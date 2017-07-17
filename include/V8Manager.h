#ifndef __V8MANAGER_H_INCLUDED__
#define __V8MANAGER_H_INCLUDED__ 

#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <v8.h>
#include <libplatform/libplatform.h>
#include "v8_utils.h"

class V8Manager
{
private:
	static V8Manager *instance;
	v8::Isolate::CreateParams create_params;
	v8::Isolate *isolate;
	v8::Platform *platform;
private:
	v8::Local<v8::Context> CreateGlobalContext(v8::Isolate *isolate);
	int RunMain(v8::Isolate *isolate, v8::Platform *platform, const char* fileName);
public:
	static V8Manager* V8Manager::Instance();
	V8Manager(V8Manager const&) = delete;
	V8Manager& operator=(V8Manager const&) = delete;
	int Run();
	void Finalize();
	static void Initialize();
private:
	V8Manager();
};

#endif