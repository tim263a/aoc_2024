#include "days/day07.h"

#include <algorithm>
#include <cstdint>
#include <cstdlib>

#include "util/print_fmt.h"
#include "util/read_input.h"

Day07::Day07()
{

}

void Day07::parseInput()
{
    read_stdio_into_buffer(m_buffer);
}

template<typename T>
static uint64_t consumeNumber(T& it)
{
    uint64_t number = 0;

    for (; *it >= '0' && *it <= '9'; it++)
    {
        number *= 10;
        number += *it - '0';
    }

    return number;
}

static uint64_t decimalShift(uint64_t prefix, uint64_t suffix)
{
    if (suffix == 0)
    {
        return prefix * 10;
    }

    uint64_t shiftedSuffix = suffix;

    while (shiftedSuffix > 0)
    {
        shiftedSuffix /= 10;
        prefix *= 10;
    }

    return prefix + suffix;
}

uint64_t Day07::calculatePart1()
{
    uint64_t sum = 0;

    std::vector<uint64_t> p1Accu1;
    std::vector<uint64_t> p1Accu2;

    std::vector<uint64_t> p2Accu1;
    std::vector<uint64_t> p2Accu2;

    int partIdx = 0;
    int lineIdx = 0;

    for (auto it = m_buffer.cbegin(); it != m_buffer.cend(); it++)
    {
        if (*it == '\n')
        {
            break;
        }

        p1Accu1.clear();
        p1Accu2.clear();
        p2Accu1.clear();
        p2Accu2.clear();

        uint64_t testValue = consumeNumber(it);
        it += 1; // consume ","

        DEBUG_FMT("{}: ", testValue);

        while (*it != '\n')
        {
            it += 1; // To skip space.

            uint64_t part = consumeNumber(it);
            DEBUG_FMT("{} ", part);

            p1Accu2.clear();
            p2Accu2.clear();

            if (!partIdx++)
            {
                p1Accu2.push_back(part);
                p2Accu2.push_back(part);
            }
            else
            {
                for (uint64_t acc1 : p1Accu1)
                {
                    uint64_t res1 = acc1 + part;
                    uint64_t res2 = acc1 * part;

                    if (testValue >= res1)
                    {
                        p1Accu2.push_back(res1);
                    }

                    if (testValue >= res2)
                    {
                        p1Accu2.push_back(res2);
                    }
                }

                for (uint64_t acc1 : p2Accu1)
                {
                    uint64_t res1 = acc1 + part;
                    uint64_t res2 = acc1 * part;

                    uint64_t res3 = decimalShift(acc1, part);

                    if (testValue >= res1)
                    {
                        p2Accu2.push_back(res1);
                    }

                    if (testValue >= res2)
                    {
                        p2Accu2.push_back(res2);
                    }

                    if (testValue >= res3)
                    {
                        p2Accu2.push_back(res3);
                    }
                }
            }

            std::swap(p1Accu1, p1Accu2);
            std::swap(p2Accu1, p2Accu2);
        }

        if (std::find(p1Accu1.cbegin(), p1Accu1.cend(), testValue) != p1Accu1.cend())
        {
            DEBUG_FMT("-1> ");
            for (auto part : p1Accu1)
            {
                DEBUG_FMT("{} ", part);
            }

            sum += testValue;
            m_part2 += testValue;
        }
        else if (std::find(p2Accu1.cbegin(), p2Accu1.cend(), testValue) != p2Accu1.cend())
        {
            DEBUG_FMT("-2> {} candidates", p2Accu1.size());

            m_part2 += testValue;
        }

        DEBUG_FMT("\n");
        lineIdx += 1;
        partIdx = 0;
    }

    return sum;
}

uint64_t Day07::calculatePart2()
{
    return m_part2;
}
