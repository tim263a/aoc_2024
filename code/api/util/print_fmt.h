#include <cstdio>
#include <format>

template<typename... Args>
void printFmt(std::format_string<Args...> format, Args... args)
{
    std::printf("%s", std::format(format, std::forward<Args>(args)...).c_str());
}
