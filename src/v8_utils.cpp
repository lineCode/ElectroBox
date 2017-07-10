#include "v8_utils.h"

using namespace v8;

const char *v8u_to_cstr(const String::Utf8Value &value) {
	return *value ? *value : "<string conversion failed>";
}



void v8u_ReportException(Isolate *isolate, TryCatch *try_catch) {
	HandleScope handle_scope(isolate);
	String::Utf8Value exception(try_catch->Exception());
	const char *exception_string = v8u_to_cstr(exception);
	Local<Message> message = try_catch->Message();
	if (message.IsEmpty()) {
		// V8 didn't provide any extra information about this error; just
		// print the exception.
		fprintf(stderr, "%s\n", exception_string);
	} else {
		// Print (filename):(line number): (message).
		String::Utf8Value filename(message->GetScriptOrigin().ResourceName());
		Local<Context> context(isolate->GetCurrentContext());
		const char *filename_string = v8u_to_cstr(filename);
		int linenum = message->GetLineNumber(context).FromJust();
		fprintf(stderr, "%s:%i: %s\n", filename_string, linenum, exception_string);
		// Print line of source code.
		String::Utf8Value sourceline(
			message->GetSourceLine(context).ToLocalChecked());
		const char *sourceline_string = v8u_to_cstr(sourceline);
		fprintf(stderr, "%s\n", sourceline_string);
		// Print wavy underline (GetUnderline is deprecated).
		int start = message->GetStartColumn(context).FromJust();
		for (int i = 0; i < start; i++) {
			fprintf(stderr, " ");
		}
		int end = message->GetEndColumn(context).FromJust();
		for (int i = start; i < end; i++) {
			fprintf(stderr, "^");
		}
		fprintf(stderr, "\n");
		Local<Value> stack_trace_string;
		if (try_catch->StackTrace(context).ToLocal(&stack_trace_string) &&
			stack_trace_string->IsString() &&
			Local<String>::Cast(stack_trace_string)->Length() > 0) {
			String::Utf8Value stack_trace(stack_trace_string);
			const char *stack_trace_string = v8u_to_cstr(stack_trace);
			fprintf(stderr, "%s\n", stack_trace_string);
		}
	}
}


bool v8u_ExecuteString(Isolate *isolate, Local<String> source, Local<Value> name, bool report_exceptions) {
	HandleScope handle_scope(isolate);
	TryCatch try_catch(isolate);
	ScriptOrigin origin(name);
	Local<Context> context(isolate->GetCurrentContext());
	Local<Script> script;
	if (!Script::Compile(context, source, &origin).ToLocal(&script)) {
		// Print errors that happened during compilation.
		if (report_exceptions)
			v8u_ReportException(isolate, &try_catch);
		return false;
	}
	else {
		Local<Value> result;
		if (!script->Run(context).ToLocal(&result)) {
			if (report_exceptions)
				v8u_ReportException(isolate, &try_catch);
			return false;
		}
		else {
			return true;
		}
	}
}


MaybeLocal<String> v8u_ReadFile(Isolate *isolate, const char *name) {
	FILE *file = fopen(name, "rb");
	if (file == NULL) return MaybeLocal<String>();

	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	rewind(file);

	char *chars = new char[size + 1];
	chars[size] = '\0';
	for (size_t i = 0; i < size;) {
		i += fread(&chars[i], 1, size - i, file);
		if (ferror(file)) {
			fclose(file);
			return MaybeLocal<String>();
		}
	}
	fclose(file);
	MaybeLocal<String> result = String::NewFromUtf8(
		isolate, chars, NewStringType::kNormal, static_cast<int>(size));
	delete[] chars;
	return result;
}