#include "days/day14.h"

#include "util/print_fmt.h"
#include "util/read_input.h"
#include <array>
#include <cstddef>
#include <cstdint>

Day14::Day14()
    : m_buffer(16 * 1024)
{

}

template<typename Iter>
uint64_t readSignedNumber(Iter& it)
{
    uint64_t number = 0;

    bool negative = *it == '-';
    it += negative;

    for (; *it >= '0' && *it <= '9'; it++)
    {
        number *= 10;
        number += *it - '0';
    }

    return negative ? -number : number;
}

void Day14::parseInput()
{
    read_stdio_into_buffer(m_buffer);

    // Format:
    // p=7,32 v=-1,-42

    for (auto it = m_buffer.cbegin(); it != m_buffer.cend(); it++)
    {
        if (*it != 'p')
        {
            break;
        }

        Puzzle puzzle {};

        it += 2; // "p="
        puzzle.x0 = readSignedNumber(it);
        it += 1; // ","
        puzzle.y0 = readSignedNumber(it);
        it += 3; // " v="
        puzzle.dX = readSignedNumber(it);
        it += 1; // ","
        puzzle.dY = readSignedNumber(it);
        it += 0; // "\n"

        m_puzzles.push_back(puzzle);
    }
}

static inline int64_t positiveModulo(int i, int n) {
    return (i % n + n) % n;
}

uint64_t Day14::calculatePart1()
{
#if 1 // Real data
    static constinit int64_t WIDTH = 101;
    static constinit int64_t HEIGHT = 103;
    static constinit int64_t STEPS = 100;

    static constinit int64_t HALF_WIDTH = 50;
    static constinit int64_t HALF_HEIGHT = 51;
#else // Example data
    static constinit int64_t WIDTH = 11;
    static constinit int64_t HEIGHT = 7;
    static constinit int64_t STEPS = 100;

    static constinit int64_t HALF_WIDTH = 5;
    static constinit int64_t HALF_HEIGHT = 3;
#endif

    uint64_t sum = 0;

    std::array<uint64_t, 4> quadrants = {};

    for (const Puzzle& p : m_puzzles)
    {
        int64_t tX = positiveModulo((p.x0 + STEPS * p.dX), WIDTH) - HALF_WIDTH;
        int64_t tY = positiveModulo((p.y0 + STEPS * p.dY), HEIGHT) - HALF_HEIGHT;

        printFmt("{} {} {} {} --> {} {}\n", p.x0, p.y0, p.dX, p.dY, tX, tY);

        if (tX == 0 || tY == 0)
        {
            continue;
        }

        std::size_t quadrant = 2 * (tX > 0) + (tY > 0);
        printFmt("--> Quadrant {}\n", quadrant);
        quadrants[quadrant] += 1;
    }

    sum = 1;
    for (auto q : quadrants)
    {
        sum *= q;
    }

    return sum;
}

uint64_t Day14::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
