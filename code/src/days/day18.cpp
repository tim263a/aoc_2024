#include "days/day18.h"

#include "util/print_fmt.h"
#include "util/read_input.h"
#include <cassert>
#include <cstddef>
#include <cstdlib>

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
        // it++; // "\n"

        m_coordinates.emplace_back(x, y);
    }

    printFmt("{} coordinates\n", m_coordinates.size());
}

#if 0 // real data
constexpr std::size_t WIDTH = 71;
constexpr std::size_t HEIGHT = 71;
constexpr std::size_t FALLS = 1000;
#else // example
constexpr std::size_t WIDTH = 7;
constexpr std::size_t HEIGHT = 7;
constexpr std::size_t FALLS = 12;
#endif

uint64_t Day18::calculatePart1()
{
    uint64_t sum = 0;

    std::vector<uint8_t> map(WIDTH * HEIGHT, '.');

    assert(m_coordinates.size() <= FALLS);

    for (std::size_t i = 0; i < FALLS; i++)
    {
        auto pos = m_coordinates[i];
        DEBUG_FMT("{} {} --> {}/{}\n",
            pos.x, pos.y, pos.y * WIDTH + pos.x, map.size());
        map[pos.y * WIDTH + pos.x] = 'X';
    }

    for (std::size_t y = 0; y < HEIGHT; y++)
    {
        for (std::size_t x = 0; x < WIDTH; x++)
        {
            printFmt("{:c}", map[y * WIDTH + x]);
        }
        printFmt("\n");
    }

    return sum;
}

uint64_t Day18::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
