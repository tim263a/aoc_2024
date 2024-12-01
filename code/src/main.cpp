#include <cstddef>
#include <cstdint>
#include <cstdio>

#include <algorithm>
#include <format>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "util/read_input.h"

int main(int argc, char** argv)
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::string> input = read_stdin_lines();
    printf("Read %lu lines from stdin\n", input.size());

    std::vector<uint32_t> l1;
    std::vector<uint32_t> l2;

    for (const std::string& line : input)
    {
        std::stringstream ss(line);

        uint32_t v1;
        uint32_t v2;

        ss >> v1 >> v2;

        l1.push_back(v1);
        l2.push_back(v2);
    }

    std::sort(l1.begin(), l1.end());
    std::sort(l2.begin(), l2.end());

    uint64_t sum = 0;

    for (size_t i = 0; i < l1.size(); i++)
    {
        int32_t v1 = l1[i];
        int32_t v2 = l2[i];

        uint32_t diff = std::abs(v1 - v2);

        printf("%s\n", std::format("{:d} {:d} {:d}", v1, v2, diff).c_str());

        sum += diff;
    }

    printf("Sum off differences: %lu\n", sum);
    return 0;
}
