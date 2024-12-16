#pragma once

#include "days/day.h"

#include <cstdint>

#include <vector>

class Day16 final
    : public Day
{
    std::vector<uint8_t> m_buffer;

public:
    Day16();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
