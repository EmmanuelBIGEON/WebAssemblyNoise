#include <emscripten.h>
#include "log.h"

void printjs(std::string &str)
{
    EM_ASM({console.log(Module.UTF8ToString($0))}, str.c_str());
}

void printjs(const char* str)
{
    EM_ASM({console.log(Module.UTF8ToString($0))}, str);
}