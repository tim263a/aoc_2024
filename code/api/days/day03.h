#pragma once

#include "days/day.h"

#include <cstdint>

#include <vector>

class Day03 final
    : public Day
{
    std::vector<uint8_t> m_buffer;
    uint64_t m_part2;

public:
    Day03();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
