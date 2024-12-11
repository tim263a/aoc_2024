#pragma once

#include "days/day.h"

#include <cstdint>

#include <vector>

class Day11 final
    : public Day
{
    std::vector<uint8_t> m_buffer;

    std::vector<uint64_t> m_inputNumbers;

public:
    Day11();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
