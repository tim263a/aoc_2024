#pragma once

#include "days/day.h"

#include <cstddef>
#include <cstdint>

#include <vector>

class Day17 final
    : public Day
{
    std::vector<uint8_t> m_buffer;

    uint64_t m_origA;
    uint64_t m_origB;
    uint64_t m_origC;

    std::vector<uint8_t> m_opCodes;

    uint64_t m_regA;
    uint64_t m_regB;
    uint64_t m_regC;

    int64_t getComboOperand(uint8_t opCode);
    std::vector<int64_t> simulate(bool abortOnOut);
    uint64_t testFor2(uint64_t prefix, std::size_t backIdx);

public:
    Day17();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
