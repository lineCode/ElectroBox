#include <iostream>
#include <sstream>
#include <string>
#include <v8.h>
#include <libplatform/libplatform.h>
#include "v8_utils.h"
#include "V8Manager.h"



int main(int argc, char *argv[]) {
	V8Manager::Initialize();
	int result = V8Manager::Instance()->Run();
	V8Manager::Instance()->Finalize();
    return result;
}