#pragma once

#include "days/day.h"

#include <cstdint>

#include <unordered_map>
#include <vector>

class Day11 final
    : public Day
{
    std::vector<uint8_t> m_buffer;

    std::vector<uint64_t> m_inputNumbers;

    std::unordered_map<uint64_t, std::vector<uint64_t>> m_lengthMap;

    uint64_t findResultLength(uint64_t value, int64_t cyclesLeft);
    void cache(uint64_t value, int64_t cyclesLeft, uint64_t result);

public:
    Day11();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
