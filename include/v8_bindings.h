#ifndef __V8BINDINGS_H_INCLUDED__
#define __V8BINDINGS_H_INCLUDED__ 

#include <v8.h>
#include <libplatform/libplatform.h>
#include "v8_utils.h"


void BindConsole(v8::Local<v8::ObjectTemplate> global, v8::Isolate *isolate);
//void BindCommonJs(v8::Local<v8::ObjectTemplate> global, v8::Isolate *isolate);


#endif