#include "V8Manager.h"
#include "v8_bindings.h"


V8Manager *V8Manager::instance = nullptr;

V8Manager::V8Manager()
{
	v8::V8::InitializeICU();
	this->platform = v8::platform::CreateDefaultPlatform();
	v8::V8::InitializePlatform(this->platform);
	v8::V8::Initialize();

	this->create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
	this->isolate = v8::Isolate::New(create_params);

	this->isolate->SetAutorunMicrotasks(false);
}

void V8Manager::Initialize() {
	V8Manager::Instance();
}

void V8Manager::Finalize()
{
	isolate->Dispose();
	v8::V8::Dispose();
	v8::V8::ShutdownPlatform();
	delete platform;
	delete create_params.array_buffer_allocator;
}

V8Manager* V8Manager::Instance() {
	if (!instance) {
		instance = new V8Manager();
	};
	return instance;
}

int V8Manager::Run() {
	v8::Isolate::Scope isolate_scope(this->isolate);
	v8::HandleScope handle_scope(this->isolate);
	v8::Local<v8::Context> context = CreateGlobalContext(this->isolate);
	if (context.IsEmpty()) {
		fprintf(stderr, "Error creating global context\n");
	}
	v8::Context::Scope context_scope(context);

	return RunMain(this->isolate, this->platform, "index.js");
}

v8::Local<v8::Context> V8Manager::CreateGlobalContext(v8::Isolate *isolate) {
	v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);
	// Global Context Bindings
	{
		BindConsole(global, isolate);
	}
	
	return v8::Context::New(isolate, NULL, global);
}


int V8Manager::RunMain(v8::Isolate *isolate, v8::Platform *platform, const char* fileName) {
	// Use all other arguments as names of files to load and run.
	v8::Local<v8::String> file_name =
		v8::String::NewFromUtf8(isolate, fileName, v8::NewStringType::kNormal)
		.ToLocalChecked();
	v8::Local<v8::String> source;
	if (!v8u_ReadFile(isolate, fileName).ToLocal(&source)) {
		fprintf(stderr, "Error reading '%s'\n", fileName);
		return 0;
	}
	bool success = v8u_ExecuteString(isolate, source, file_name, true);
	while (v8::platform::PumpMessageLoop(platform, isolate)) continue;
	if (!success) return 1;
}