#pragma once

#include "days/day.h"

#include <cstdint>

#include <tuple>
#include <unordered_set>
#include <vector>
#include <unordered_map>

class Day06 final
    : public Day
{
    struct Segment
    {
        int orthoPos;

        int start;
        int end;
    };

    std::unordered_map<int, std::vector<int>> m_wallsX;
    std::unordered_map<int, std::vector<int>> m_wallsY;

    std::vector<Segment> m_segmentsX;
    std::vector<Segment> m_segmentsY;

    std::vector<uint8_t> m_buffer;

    std::unordered_set<int> m_visited;

public:
    Day06();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
