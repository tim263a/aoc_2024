#pragma once

#include "days/day.h"

#include <cstdint>

#include <unordered_map>
#include <vector>

class Day05 final
    : public Day
{
    using iterator_type = std::vector<uint8_t>::const_iterator;

    std::vector<uint8_t> m_buffer;
    std::unordered_map<int, std::vector<int>> m_ordering;

    iterator_type m_itUpdates;

    int orderAndQuery(std::vector<int> lineNumbers);

    int m_part2;

public:
    Day05();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
