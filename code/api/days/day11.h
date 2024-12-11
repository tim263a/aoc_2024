#pragma once

#include "days/day.h"

#include <cstdint>

#include <optional>
#include <unordered_map>
#include <vector>

class Day11 final
    : public Day
{
    std::vector<uint8_t> m_buffer;

    std::vector<uint64_t> m_inputNumbers;

    std::unordered_map<uint64_t, uint64_t> m_cache;

    uint64_t findResultLength(uint64_t value, int64_t cyclesLeft, uint64_t maxCycles);

    void cache(uint64_t value, int64_t cyclesLeft, int64_t maxCycles, uint64_t result);
    std::optional<uint64_t> queryCache(uint64_t value, int64_t cyclesLeft, int64_t maxCycles);

public:
    Day11();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
