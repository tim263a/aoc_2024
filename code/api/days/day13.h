#pragma once

#include "days/day.h"

#include <cstdint>

#include <vector>

class Day13 final
    : public Day
{
    struct Puzzle
    {
        int64_t dX1;
        int64_t dY1;
        int64_t dX2;
        int64_t dY2;

        int64_t tX;
        int64_t tY;
    };

    std::vector<uint8_t> m_buffer;
    std::vector<Puzzle> m_puzzles;

public:
    Day13();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
