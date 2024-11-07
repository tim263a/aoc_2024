#include <cstdio>

#include <iostream>
#include <string>

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

int main(int argc, char** argv)
{
    std::string input = read_stdin();
    printf("Read %lu characters from stdin\n", input.size());

    return 0;
}
