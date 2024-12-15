#include "days/day14.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>

#include "util/print_fmt.h"
#include "util/read_input.h"

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

static inline constexpr int64_t positiveModulo(int i, int n) {
    return (i % n + n) % n;
}

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

uint64_t Day14::calculatePart1()
{
    uint64_t sum = 0;

    std::array<uint64_t, 4> quadrants = {};

    for (const Puzzle& p : m_puzzles)
    {
        int64_t tX = positiveModulo((p.x0 + STEPS * p.dX), WIDTH) - HALF_WIDTH;
        int64_t tY = positiveModulo((p.y0 + STEPS * p.dY), HEIGHT) - HALF_HEIGHT;

        DEBUG_FMT("{} {} {} {} --> {} {}\n", p.x0, p.y0, p.dX, p.dY, tX, tY);

        if (tX == 0 || tY == 0)
        {
            continue;
        }

        std::size_t quadrant = 2 * (tX > 0) + (tY > 0);
        DEBUG_FMT("--> Quadrant {}\n", quadrant);
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
    struct Position
    {
        uint64_t x;
        uint64_t y;
    };

    // std::vector<Position> positions;

    uint64_t candidates = 0;

    int64_t minOrthoX = 2024;
    int64_t minOrthoY = 2024;

    int64_t bestIdx = 0;

    for (int64_t steps = 0; steps < 10000 || !bestIdx; /* positions.clear(), */ steps++)
    {
        int64_t outliersX = 0;
        int64_t outliersY = 0;

        static constinit int64_t THRESHOLD_X = 30;
        static constinit int64_t THRESHOLD_Y = 30;

        static constinit int64_t RENDER_DISTANCE_X = 100;
        static constinit int64_t RENDER_DISTANCE_Y = 100;

#if 0
        bool skip = false; // Actually makes things slower.
#endif

        for (const Puzzle& p : m_puzzles)
        {
            int64_t tX = positiveModulo(p.x0 + steps * p.dX, WIDTH);
            int64_t tY = positiveModulo(p.y0 + steps * p.dY, HEIGHT);

            if (tX < THRESHOLD_X)
            {
                outliersX++;

#if 0
                if (outliersX > minOrthoY)
                {
                    skip = true;
                    break;
                }
#endif
            }

            if (tY < THRESHOLD_Y)
            {
                outliersY++;

#if 0
                if (outliersY > minOrthoX)
                {
                    skip = true;
                    break;
                }
#endif
            }

            // positions.emplace_back(tX, tY);
        }

#if 0
        if (skip)
        {
            continue;
        }
#endif

        if (outliersX > RENDER_DISTANCE_X && outliersY > RENDER_DISTANCE_Y)
        {
            continue;
        }

        bool isOrthoMinX = outliersX < RENDER_DISTANCE_X && outliersY < minOrthoX;
        bool isOrthoMinY = outliersY < RENDER_DISTANCE_Y && outliersX < minOrthoY;

        if (isOrthoMinX && isOrthoMinY)
        {
            bestIdx = steps;
            break;
        }

        if (!isOrthoMinX && !isOrthoMinY)
        {
            continue;
        }

        if (isOrthoMinX)
        {
            minOrthoX = outliersY;
            printFmt("MinOrthoX: {}\n", minOrthoX);
        }

        if (isOrthoMinY)
        {
            minOrthoY = outliersX;
            printFmt("MinOrthoY: {}\n", minOrthoY);
        }

        candidates++;

#if 0
        for (uint64_t y = 0; y < HEIGHT; y++)
        {
            for (uint64_t x = 0; x < WIDTH; x++)
            {
                if (std::find_if(positions.cbegin(), positions.cend(),
                    [&] (const Position& p)
                    {
                        return p.x == x && p.y == y;
                    }) != positions.cend())
                {
                    printFmt("{:c}", 'X');
                }
                else
                {
                    printFmt("{:c}", ' ');
                }
            }
            printFmt("\n");
        }
#endif

        printFmt("Above after {} steps, outliers {} {}\n",
            steps, outliersX, outliersY);

        // std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return bestIdx;
}
