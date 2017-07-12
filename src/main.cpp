#include <iostream>
#include <sstream>
#include <string>
#include <v8.h>
#include <libplatform\libplatform.h>
#include "v8_utils.h"



void Print(const v8::FunctionCallbackInfo<v8::Value>& args) {
	v8::HandleScope handle_scope(args.GetIsolate());
	v8::String::Utf8Value str(args[0]);
	const char* cstr = v8u_to_cstr(str);
	printf("%s\n", cstr);
	fflush(stdout);
}


v8::Local<v8::Context> CreateShellContext(v8::Isolate *isolate) {
// Create a template for the global object.
    v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
    global->Set(v8::String::NewFromUtf8(isolate, "window"), v8::ObjectTemplate::New(isolate));
	global->Set(v8::String::NewFromUtf8(isolate, "window"), v8::ObjectTemplate::New(isolate));
    global->Set(v8::String::NewFromUtf8(isolate, "print"), v8::FunctionTemplate::New(isolate, &Print));
    return v8::Context::New(isolate, NULL, global);
}







int RunMain(v8::Isolate *isolate, v8::Platform *platform, const char* fileName) {

    // Use all other arguments as names of files to load and run.
    v8::Local<v8::String> file_name =
            v8::String::NewFromUtf8(isolate, fileName, v8::NewStringType::kNormal)
                    .ToLocalChecked();
    v8::Local<v8::String> source;
    if (!v8u_ReadFile(isolate, fileName).ToLocal(&source)) {
        fprintf(stderr, "Error reading '%s'\n", fileName);
    }
    bool success = v8u_ExecuteString(isolate, source, file_name, true);
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

    isolate->SetAutorunMicrotasks(false);

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
	//system("pause");
    return result;
}