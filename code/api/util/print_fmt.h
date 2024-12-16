#pragma once

#include <cstdio>
#include <format>

extern bool g_verbose;

template<typename... Args>
void printFmt(std::format_string<Args...> format, Args... args)
{
    std::printf("%s", std::format(format, std::forward<Args>(args)...).c_str());
}


template<typename... Args>
void debugFmt(std::format_string<Args...> format, Args... args)
{
    if (g_verbose)
    {
        std::printf("%s", std::format(format, std::forward<Args>(args)...).c_str());
    }
}

#ifndef NDEBUG
    #define DEBUG_FMT(...) \
        if (g_verbose) debugFmt(__VA_ARGS__)
#else
    #define DEBUG_FMT(...) ;
#endif
