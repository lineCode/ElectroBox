#include "v8_bindings.h"

void Print(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::HandleScope handle_scope(args.GetIsolate());
	v8::String::Utf8Value str(args[0]);
	const char* cstr = v8u_to_cstr(str);
	printf("%s\n", cstr);
	fflush(stdout);
}


void BindConsole(v8::Local<v8::ObjectTemplate> global, v8::Isolate *isolate) {
	global->Set(v8::String::NewFromUtf8(isolate, "print"), v8::FunctionTemplate::New(isolate, &Print));
	global->Set(v8::String::NewFromUtf8(isolate, "alert"), v8::FunctionTemplate::New(isolate, &Print));
}