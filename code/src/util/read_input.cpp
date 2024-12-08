#include "util/read_input.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>

#include <cstdint>
#include <cstddef>
#include <iostream>

void read_stdio_into_buffer(std::vector<uint8_t>& buffer)
{
    constexpr uint_fast32_t FALLBACK_SIZE { 1024 };

    uint_fast32_t alreadyRead = 0;
    uint_fast32_t batchSize = buffer.size();
    while (std::cin.read((char*) buffer.data() + alreadyRead, batchSize)) [[unlikely]]
    {
        alreadyRead += batchSize;
        batchSize = FALLBACK_SIZE;
        buffer.resize(alreadyRead + batchSize);

#ifdef NDEBUG
        std::cerr << "Warning: Input buffer resize was required " <<
            alreadyRead << " --> " << (alreadyRead + batchSize) << std::endl;
#endif
    }

    alreadyRead += std::cin.gcount();
    buffer.resize(alreadyRead);

    if (std::cin.fail() && !std::cin.eof()) [[unlikely]]
    {
        std::cerr << "Error reading input\n";
        std::exit(1);
    }
}

void read_stdio_into_buffer_unistd(std::vector<uint8_t>& buffer)
{
    constexpr std::size_t FALLBACK_SIZE { 1024 };

    ssize_t alreadyRead = 0;
    ssize_t batchSize = buffer.size();

    ssize_t bytesRead = 0;
    do
    {
        alreadyRead += bytesRead;
        if (alreadyRead) [[unlikely]]
        {
            alreadyRead += batchSize;
            batchSize = FALLBACK_SIZE;
            buffer.resize(alreadyRead + batchSize);

#ifdef NDEBUG
            printf("Warning: Input buffer resized %d -> %d\n",
                alreadyRead, alreadyRead + batchSize);
#endif
        }

        bytesRead = read(STDIN_FILENO, buffer.data() + alreadyRead, batchSize);
    } while (bytesRead > 0 && bytesRead < batchSize);

    if (bytesRead < 0)
    {
        printf("Could not read from stdin: %s\n", strerror(errno));
        std::exit(1);
    }
}

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
