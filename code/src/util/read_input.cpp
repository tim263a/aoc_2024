#include "util/read_input.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>

#include <cstdint>
#include <cstddef>
#include <iostream>

void read_stdio_into_buffer(std::vector<uint8_t>& buffer, bool verbose)
{
    constexpr std::size_t FALLBACK_SIZE { 1024 };

    if (buffer.size() == 0)
    {
        buffer.resize(FALLBACK_SIZE);
    }

    ssize_t alreadyRead = 0;
    ssize_t batchSize = buffer.size();

    ssize_t bytesRead = 0;
    do
    {
        alreadyRead += bytesRead;
        if (alreadyRead) [[unlikely]]
        {
            batchSize = FALLBACK_SIZE;
            buffer.resize(alreadyRead + batchSize);

            printf("Warning: Input buffer resized %ld -> %ld\n",
                alreadyRead, alreadyRead + batchSize);
        }

        bytesRead = read(STDIN_FILENO, buffer.data() + alreadyRead, batchSize);
        if (verbose)
        {
            printf("Bytes read: %ld\n", bytesRead);
        }
    } while (bytesRead > 0 && bytesRead >= batchSize);

    if (bytesRead < 0)
    {
        printf("Could not read from stdin: %s\n", strerror(errno));
        std::exit(1);
    }
    else
    {
        alreadyRead += bytesRead;
        buffer.resize(alreadyRead + 1);
        *buffer.rbegin() = '\0';

        if (verbose)
        {
            printf("Info: Input buffer resized -> %ld\n", alreadyRead + 1);
        }
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
