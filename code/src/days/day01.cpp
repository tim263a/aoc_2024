#include "days/day01.h"

#include <algorithm>
#include <sstream>
#include <vector>

#include "util/print_fmt.h"
#include "util/read_input.h"

void Day01::parseInput()
{
    std::vector<std::string> input = read_stdin_lines();

    size_t nLines = input.size();
    debugFmt("Read {:d} lines from stdin\n", nLines);
    l1.reserve(nLines);
    l2.reserve(nLines);

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
}

uint64_t Day01::calculatePart1()
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

uint64_t Day01::calculatePart2()
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
