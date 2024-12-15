#include "days/day11.h"

#include "util/print_fmt.h"
#include "util/read_input.h"

#include <algorithm>
#include <cassert>
#include <map>
#include <optional>
#include <sstream>
#include <unistd.h>
#include <unordered_map>

Day11::Day11()
    : m_buffer(100)
{
}

void Day11::parseInput()
{
    read_stdio_into_buffer(m_buffer);

    std::string inputString(m_buffer.cbegin(), m_buffer.cend());
    std::stringstream stream(inputString);

    int number = 0;
    while (stream >> number) {
        m_inputNumbers.push_back(number);
    }
}

static bool splitEven(uint64_t v, uint64_t& left, uint64_t& right)
{
    uint64_t numberLength = 0;
    for (uint64_t shifted = 1; v >= shifted; numberLength++, shifted *= 10) { }

    DEBUG_FMT("NumberLength {}: {}\n", v, numberLength);

    if (numberLength % 2)
    {
        return false;
    }

    left = v;
    right = 0;

    uint64_t rightShift = 1;

    for (uint64_t i = 0; i < numberLength / 2; i++)
    {
        right += (left % 10) * rightShift;
        rightShift *= 10;
        left /= 10;
    }

    DEBUG_FMT("Split {} -> {} {}\n", v, left, right);

    return true;
}

uint64_t Day11::calculatePart1()
{
    uint64_t sum = 0;

    std::unordered_map<uint64_t, uint64_t> o0;
    std::unordered_map<uint64_t, uint64_t> o1;

    for (uint64_t v : m_inputNumbers)
    {
        o0[v] += 1;
    }

    int64_t nExpansions = 0;

    for (int i = 0; i < 75; i++)
    {
        uint64_t sum = 0;

        for (auto e0 : o0)
        {
            nExpansions += 1;

            auto v = e0.first;
            auto multitude = e0.second;

            sum += multitude;

            if (v == 0)
            {
                o1[1] += multitude;
                continue;
            }

            uint64_t left = 0;
            uint64_t right = 0;

            if (splitEven(v, left, right))
            {
                o1[left] += multitude;
                o1[right] += multitude;

                sum += multitude;
            }
            else
            {
                o1[2024 * v] += multitude;
            }
        }

        if (i == 24)
        {
            m_part1 = sum;
        }
        else if (i == 74)
        {
            m_part2 = sum;
        }

#if 0
        for (uint64_t v : v1)
        {
            printFmt("{} ", v);
        }
        printFmt("\n");
#endif

        printFmt("Iteration {}: {} ({} unique, {} expansions)\n",
            i, sum, o1.size(), nExpansions);

        o0 = std::move(o1);
        o1.clear();
    }

    return m_part1;
}

uint64_t Day11::calculatePart2()
{
    return m_part2;
}
