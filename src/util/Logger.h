#pragma once

#include <string>

class Logger
{
    public:
        static void Log(const std::string& str);
        static void Log(const char* str);
        static void Log(unsigned long value);
};