#include "Logger.h"

#include <emscripten.h>

void Logger::Log(const std::string& str)
{
    EM_ASM({console.log(Module.UTF8ToString($0))}, str.c_str());
}

void Logger::Log(const char* str)
{
    EM_ASM({console.log(Module.UTF8ToString($0))}, str);
}

void Logger::Log(unsigned long value)
{
    EM_ASM({console.log(Module.UTF8ToString($0))}, std::to_string(value).c_str());
}

void Logger::Log(unsigned int value)
{
    EM_ASM({console.log(Module.UTF8ToString($0))}, std::to_string(value).c_str());
}

void Logger::Log(int value)
{
    EM_ASM({console.log(Module.UTF8ToString($0))}, std::to_string(value).c_str());
}

void Logger::Log(float value)
{
    EM_ASM({console.log(Module.UTF8ToString($0))}, std::to_string(value).c_str());
}