#include "days/day13.h"

#include "util/print_fmt.h"
#include "util/read_input.h"

#include <iostream>

Day13::Day13()
    : m_buffer(32000)
{

}

template<typename Iter>
uint64_t readNumber(Iter& it)
{
    uint64_t number = 0;

    for (; *it >= '0' && *it <= '9'; it++)
    {
        number *= 10;
        number += *it - '0';
    }

    return number;
}

void Day13::parseInput()
{
    read_stdio_into_buffer(m_buffer);

    // Format:
    // Button A: X+56, Y+17
    // Button B: X+33, Y+61
    // Prize: X=5469, Y=5178

    uint64_t number = 0;

    for (auto it = m_buffer.cbegin(); it != m_buffer.cend(); it++)
    {
        if (*it != 'B')
        {
            break;
        }

        Puzzle puzzle {};

        it += 12; // "Button A: X+"
        puzzle.dX1 = readNumber(it);
        it += 4; // ", Y+"
        puzzle.dY1 = readNumber(it);
        it += 13; // "\nButton B: X+"
        puzzle.dX2 = readNumber(it);
        it += 4; // ", Y+"
        puzzle.dY2 = readNumber(it);
        it += 10; // "\nPrize: X="
        puzzle.tX = readNumber(it);
        it += 4; // ", Y="
        puzzle.tY = readNumber(it);
        it += 1; // "\n"

        // printFmt("t0*({} {})+t1*({} {}) -> ({} {})\n",
            // puzzle.buttonAX, puzzle.buttonAY,
            // puzzle.buttonBX, puzzle.buttonBY,
            // puzzle.prizeX, puzzle.prizeY);

        m_puzzles.push_back(puzzle);
    }
}

static bool iterate(
    int64_t x1, int64_t y1, int64_t x2, int64_t y2,
    int64_t tx, int64_t ty, uint64_t& a, uint64_t& b,
    uint64_t maxLimit)
{
    a = std::max(tx / x1 + 1, ty / y1 + 1);
    a = std::min<int64_t>(a, maxLimit);

    b = 0;

    int64_t posX = a * x1;
    int64_t posY = a * y1;

    uint64_t iterations = 0;

    while ((a > 0 && iterations < 100) && (posX > tx || posY > ty || !iterations))
    {
        iterations++;

        a -= 1;
        posX -= x1;
        posY -= y1;

        while (posX < tx || posY < ty)
        {
            b += 1;
            posX += x2;
            posY += y2;
        }

        if (b > maxLimit)
        {
            break;
        }

        printFmt("a {} b {} posX {} posY {}\n", a, b, posX, posY);
    }

    return posX == tx && posY == ty;
}

uint64_t Day13::calculatePart1()
{
    uint64_t sum = 0;

    for (Puzzle p : m_puzzles)
    {
        if ((100 * p.dX1 + 100 * p.dX2 < p.tX) ||
            (100 * p.dY1 + 100 * p.dY2 < p.tY))
        {
            printFmt("{:3}|{:3} {:3}|{:3} -> {:5}|{:5} --> > 100\n",
                p.dX1, p.dY1, p.dX2, p.dY2, p.tX, p.tY);
            continue;
        }

        double upper = p.tX * p.dY2 - p.tY * p.dX2;
        double lower = p.tY * p.dX1 - p.tX * p.dY1;
        double ratio = std::abs(upper / lower);

        uint64_t a = 0;
        uint64_t b = 0;

        bool valid = false;

        if (ratio < 3)
        {
            valid = iterate(p.dX1, p.dY1, p.dX2, p.dY2, p.tX, p.tY, a, b, 100);
        }
        else
        {
            valid = iterate(p.dX2, p.dY2, p.dX1, p.dY1, p.tX, p.tY, b, a, 100);
        }

        printFmt("{:3}|{:3} {:3}|{:3} -> {:5}|{:5} --> ratio {:+8} / {:+8} = {:+5.2f} --> a {:3} b {:3} valid {}\n",
            p.dX1, p.dY1, p.dX2, p.dY2, p.tX, p.tY,
            upper, lower, ratio,
            a, b, valid);

        if (valid)
        {
            sum += 3 * a;
            sum += 1 * b;
        }
    }

    return sum;
}

uint64_t Day13::calculatePart2()
{
    uint64_t sum = 0;

    for (Puzzle p : m_puzzles)
    {
        p.tX += 10000000000000ULL;
        p.tY += 10000000000000ULL;

        double upper = p.tX * p.dY2 - p.tY * p.dX2;
        double lower = p.tY * p.dX1 - p.tX * p.dY1;
        double ratio = std::abs(upper / lower);

        uint64_t a = 0;
        uint64_t b = 0;

        bool valid = false;

        if (ratio < 3)
        {
            valid = iterate(p.dX1, p.dY1, p.dX2, p.dY2, p.tX, p.tY, a, b, -1ULL);
        }
        else
        {
            valid = iterate(p.dX2, p.dY2, p.dX1, p.dY1, p.tX, p.tY, b, a, -1ULL);
        }

        printFmt("{:3}|{:3} {:3}|{:3} -> {:5}|{:5} --> ratio {:+8} / {:+8} = {:+5.2f} --> a {:3} b {:3} valid {}\n",
            p.dX1, p.dY1, p.dX2, p.dY2, p.tX, p.tY,
            upper, lower, ratio,
            a, b, valid);

        if (valid)
        {
            sum += 3 * a;
            sum += 1 * b;
        }
    }

    return sum;
}
