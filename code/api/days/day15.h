#pragma once

#include "days/day.h"

#include <cstdint>

#include <vector>

class Day15 final
    : public Day
{
    std::vector<uint8_t> m_buffer;

    int64_t m_width;
    int64_t m_height;

    int64_t m_startX;
    int64_t m_startY;

    int64_t m_idxDirections;

    uint8_t& mapAt(std::size_t x, std::size_t y);

public:
    Day15();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
