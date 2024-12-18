#pragma once

#include "days/day.h"

#include <cstdint>

#include <vector>

class Day18 final
    : public Day
{
    std::vector<uint8_t> m_buffer;

    struct Coordinate
    {
        int64_t x;
        int64_t y;
    };
    std::vector<Coordinate> m_coordinates;

public:
    Day18();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
