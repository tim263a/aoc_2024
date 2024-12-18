#include "days/day18.h"

#include "util/print_fmt.h"
#include "util/read_input.h"

Day18::Day18()
    : m_buffer(32000)
{

}

template<typename Iter>
static uint64_t readNumber(Iter& it)
{
    uint64_t number = 0;

    for (; *it >= '0' && *it <= '9'; it++)
    {
        number *= 10;
        number += *it - '0';
    }

    return number;
}

void Day18::parseInput()
{
    read_stdio_into_buffer(m_buffer);

    for (auto it = m_buffer.cbegin(); *it != '\0'; it++)
    {
        int64_t x = readNumber(it);
        it++; // ","
        int64_t y = readNumber(it);
        it++; // "\n"

        m_coordinates.emplace_back(x, y);
    }

    printFmt("{} coordinates\n", m_coordinates.size());
}

uint64_t Day18::calculatePart1()
{
    uint64_t sum = 0;

    return sum;
}

uint64_t Day18::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
