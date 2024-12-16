#include "days/day11.h"

#include "util/print_fmt.h"
#include "util/read_input.h"

#include <algorithm>
#include <cassert>
#include <map>
#include <memory>
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
    uint64_t fullShift = 1;
    uint64_t halfShift = 1;
    bool isOdd = false;

    while (fullShift <= v)
    {
        fullShift *= 10;
        halfShift *= isOdd ? 1 : 10;
        isOdd = !isOdd;

        DEBUG_FMT("full {} half {}\n", fullShift, halfShift);
    }

    left = v / halfShift;
    right = v - left * halfShift;

    return !isOdd;
}

uint64_t Day11::calculatePart1()
{
    // Allocate enough buckets so that map shouldn't be forced to create linked list.
    auto p0 = std::make_unique<std::unordered_map<uint64_t, uint64_t>>(16000);
    auto p1 = std::make_unique<std::unordered_map<uint64_t, uint64_t>>(16000);

    for (uint64_t v : m_inputNumbers)
    {
        (*p0)[v]++;
    }

    int64_t nExpansions = 0;

    for (int i = 0; i < 75; i++)
    {
        auto& o0 = *p0;
        auto& o1 = *p1;

        uint64_t sum = 0;

        for (auto e0 : o0)
        {
            nExpansions += 1;

            const auto v = e0.first;
            const auto multitude = e0.second;

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
        for (auto e1 : o1)
        {
            printFmt("{} ", e1.first);
        }
        printFmt("\n");
#endif

        DEBUG_FMT("Iteration {}: {} ({} unique, {} expansions)\n",
            i, sum, o1.size(), nExpansions);

        std::swap(p0, p1);
        p1->clear();

        // p1->rehash(16000);
    }

    return m_part1;
}

uint64_t Day11::calculatePart2()
{
    return m_part2;
}
