#ifndef __V8UTILS_H_INCLUDED__
#define __V8UTILS_H_INCLUDED__ 

#include <iostream>
#include <sstream>
#include <string>
#include <v8.h>
#include <libplatform\libplatform.h>


const char *v8u_to_cstr(const v8::String::Utf8Value &value);
void v8u_ReportException(v8::Isolate *isolate, v8::TryCatch *try_catch);
bool v8u_ExecuteString(v8::Isolate *isolate, v8::Local<v8::String> source, v8::Local<v8::Value> name, bool report_exceptions);
v8::MaybeLocal<v8::String> v8u_ReadFile(v8::Isolate *isolate, const char *name);



#endif