#pragma once

#include "days/day.h"

#include <cstddef>
#include <cstdint>

#include <vector>

class Day12 final
    : public Day
{
    std::vector<uint8_t> m_buffer;

    std::size_t m_width;
    std::size_t m_height;

public:
    Day12();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
