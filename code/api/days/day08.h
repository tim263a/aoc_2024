#pragma once

#include "days/day.h"

#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Day08 final
    : public Day
{
    std::vector<uint8_t> m_buffer;

    std::unordered_map<int, std::vector<std::pair<int, int>>> m_positions;
    std::unordered_set<int> m_hashes;
    std::unordered_set<int> m_hashes2;

    uint64_t m_part2 = 0;

    void addHash(int width, int x, int y);

public:
    Day08();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
