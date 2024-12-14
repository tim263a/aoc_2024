#pragma once

#include "days/day.h"

#include <cstdint>

#include <vector>

class Day14 final
    : public Day
{
    struct Puzzle
    {
        int64_t x0;
        int64_t y0;

        int64_t dX;
        int64_t dY;
    };

    std::vector<uint8_t> m_buffer;
    std::vector<Puzzle> m_puzzles;

public:
    Day14();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
