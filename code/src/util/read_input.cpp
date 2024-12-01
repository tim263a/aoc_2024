#include "util/read_input.h"

#include <cstddef>
#include <iostream>

std::string read_stdin()
{
    constexpr size_t BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    std::string input;
    input.reserve(BUFFER_SIZE);

    while (std::cin.read(buffer, BUFFER_SIZE)) {
        input.append(buffer, std::cin.gcount());
    }

    if (std::cin.fail() && !std::cin.eof())
    {
        std::cerr << "Error reading input\n";
        std::exit(1);
    }

    return input;
}

std::vector<std::string> read_stdin_lines()
{
    std::vector<std::string> result;

    std::string line;
    while (std::getline(std::cin, line))
    {
        result.push_back(line);
    }

    if (std::cin.fail() && !std::cin.eof())
    {
        std::cerr << "Error reading input\n";
        std::exit(1);
    }

    return result;
}
