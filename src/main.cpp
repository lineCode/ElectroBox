#include <iostream>
#include <sstream>
#include <string>
#include "v8/v8.h"
#include "v8/libplatform/libplatform.h"

const char *ToCString(const v8::String::Utf8Value &value) {
    return *value ? *value : "<string conversion failed>";
}
void Print(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::HandleScope handle_scope(args.GetIsolate());
    v8::String::Utf8Value str(args[0]);
    const char* cstr = ToCString(str);
    printf("%s\n", cstr);
    fflush(stdout);
}


v8::Local<v8::Context> CreateShellContext(v8::Isolate *isolate) {
// Create a template for the global object.
    v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
    global->Set(v8::String::NewFromUtf8(isolate, "console"), v8::ObjectTemplate::New(isolate));
    global->Set(v8::String::NewFromUtf8(isolate, "print"), v8::FunctionTemplate::New(isolate, &Print));
    return v8::Context::New(isolate, NULL, global);
}

v8::MaybeLocal<v8::String> ReadFile(v8::Isolate *isolate, const char *name) {
    FILE *file = fopen(name, "rb");
    if (file == NULL) return v8::MaybeLocal<v8::String>();

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    char *chars = new char[size + 1];
    chars[size] = '\0';
    for (size_t i = 0; i < size;) {
        i += fread(&chars[i], 1, size - i, file);
        if (ferror(file)) {
            fclose(file);
            return v8::MaybeLocal<v8::String>();
        }
    }
    fclose(file);
    v8::MaybeLocal<v8::String> result = v8::String::NewFromUtf8(
            isolate, chars, v8::NewStringType::kNormal, static_cast<int>(size));
    delete[] chars;
    return result;
}

void ReportException(v8::Isolate *isolate, v8::TryCatch *try_catch) {
    v8::HandleScope handle_scope(isolate);
    v8::String::Utf8Value exception(try_catch->Exception());
    const char *exception_string = ToCString(exception);
    v8::Local<v8::Message> message = try_catch->Message();
    if (message.IsEmpty()) {
        // V8 didn't provide any extra information about this error; just
        // print the exception.
        fprintf(stderr, "%s\n", exception_string);
    } else {
        // Print (filename):(line number): (message).
        v8::String::Utf8Value filename(message->GetScriptOrigin().ResourceName());
        v8::Local<v8::Context> context(isolate->GetCurrentContext());
        const char *filename_string = ToCString(filename);
        int linenum = message->GetLineNumber(context).FromJust();
        fprintf(stderr, "%s:%i: %s\n", filename_string, linenum, exception_string);
        // Print line of source code.
        v8::String::Utf8Value sourceline(
                message->GetSourceLine(context).ToLocalChecked());
        const char *sourceline_string = ToCString(sourceline);
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
        v8::Local<v8::Value> stack_trace_string;
        if (try_catch->StackTrace(context).ToLocal(&stack_trace_string) &&
            stack_trace_string->IsString() &&
            v8::Local<v8::String>::Cast(stack_trace_string)->Length() > 0) {
            v8::String::Utf8Value stack_trace(stack_trace_string);
            const char *stack_trace_string = ToCString(stack_trace);
            fprintf(stderr, "%s\n", stack_trace_string);
        }
    }
}

bool ExecuteString(v8::Isolate *isolate, v8::Local<v8::String> source, v8::Local<v8::Value> name, bool report_exceptions) {
    v8::HandleScope handle_scope(isolate);
    v8::TryCatch try_catch(isolate);
    v8::ScriptOrigin origin(name);
    v8::Local<v8::Context> context(isolate->GetCurrentContext());
    v8::Local<v8::Script> script;
    if (!v8::Script::Compile(context, source, &origin).ToLocal(&script)) {
        // Print errors that happened during compilation.
        if (report_exceptions)
            ReportException(isolate, &try_catch);
        return false;
    } else {
        v8::Local<v8::Value> result;
        if (!script->Run(context).ToLocal(&result)) {
            if (report_exceptions)
                ReportException(isolate, &try_catch);
            return false;
        } else {
            return true;
        }
    }
}


int RunMain(v8::Isolate *isolate, v8::Platform *platform, const char* fileName) {

    // Use all other arguments as names of files to load and run.
    v8::Local<v8::String> file_name =
            v8::String::NewFromUtf8(isolate, fileName, v8::NewStringType::kNormal)
                    .ToLocalChecked();
    v8::Local<v8::String> source;
    if (!ReadFile(isolate, fileName).ToLocal(&source)) {
        fprintf(stderr, "Error reading '%s'\n", fileName);
    }
    bool success = ExecuteString(isolate, source, file_name, true);
    while (v8::platform::PumpMessageLoop(platform, isolate)) continue;
    if (!success) return 1;
}


int main(int argc, char *argv[]) {
    v8::V8::InitializeICU();
    v8::Platform *platform = v8::platform::CreateDefaultPlatform();
    v8::V8::InitializePlatform(platform);
    v8::V8::Initialize();



    v8::Isolate::CreateParams create_params;
    create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();

    v8::Isolate *isolate = v8::Isolate::New(create_params);

    int result;
    {
        v8::Isolate::Scope isolate_scope(isolate);
        v8::HandleScope handle_scope(isolate);
        v8::Local<v8::Context> context = CreateShellContext(isolate);
        if (context.IsEmpty()) {
            fprintf(stderr, "Error creating context\n");
            return 1;
        }
        v8::Context::Scope context_scope(context);
        result = RunMain(isolate, platform, "index.js");
    }
    isolate->Dispose();
    v8::V8::Dispose();
    v8::V8::ShutdownPlatform();
    delete platform;
    delete create_params.array_buffer_allocator;
    return result;
}