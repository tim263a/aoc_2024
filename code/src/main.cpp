#include <cstddef>
#include <cstdint>
#include <cstdio>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "util/read_input.h"
#include "util/print_fmt.h"

bool g_verbose = false;

uint64_t calculatePart1Sum(
    const std::vector<uint32_t>& l1,
    const std::vector<uint32_t>& l2)
{
    uint64_t sum = 0;

    for (size_t i = 0; i < l1.size(); i++)
    {
        int32_t v1 = l1[i];
        int32_t v2 = l2[i];

        uint32_t diff = std::abs(v1 - v2);

        debugFmt("{:d} {:d} {:d}\n", v1, v2, diff);

        sum += diff;
    }

     debugFmt("Sum off differences: {:d}\n", sum);

    return sum;
}

uint64_t calculatePart2Sum(
    const std::vector<uint32_t>& l1,
    const std::vector<uint32_t>& l2)
{
    // Lists are already sorted, due to part 1.

    uint64_t sum = 0;

    size_t i1 = 0;
    size_t i2 = 0;

    while (i1 < l1.size())
    {
        uint32_t vLeft = l1[i1];

        while (l2[i2] < vLeft)
        {
            i2++;
        }

        uint8_t multitude = 0;

        while (l2[i2] == vLeft)
        {
            i2++;
            multitude += 1;
        }

        i1++;

        sum += vLeft * multitude;

         debugFmt("{:d} {:d} {:d}\n", vLeft, multitude, sum);
    }

    return sum;
}

int main(int argc, char** argv)
{
    uint32_t dayIdx = argc >= 2 ? std::stoi(argv[1]) : DAY_IDX;
    g_verbose = argc >= 3 && (argv[2] == std::string("1"));

    debugFmt("Running for day {:d}, ", dayIdx);
    debugFmt("debug {:s}\n", g_verbose ? "enabled" : "disabled");

    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::string> input = read_stdin_lines();
    printFmt("Read {:d} lines from stdin\n", input.size());

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

    // Need to sort anyway - so no need for a hash map.
    std::sort(l1.begin(), l1.end());
    std::sort(l2.begin(), l2.end());

    uint64_t part1 = calculatePart1Sum(l1, l2);
    uint64_t part2 = calculatePart2Sum(l1, l2);

    printFmt("Solution part 1: {:d}\n", part1);
    printFmt("Solution part 2: {:d}\n", part2);

    return 0;
}
