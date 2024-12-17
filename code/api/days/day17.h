#pragma once

#include "days/day.h"

#include <cstdint>

#include <vector>

class Day17 final
    : public Day
{
    std::vector<uint8_t> m_buffer;

    uint64_t m_regA;
    uint64_t m_regB;
    uint64_t m_regC;

    std::vector<uint8_t> m_opCodes;

public:
    Day17();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
