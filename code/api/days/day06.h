#pragma once

#include "days/day.h"

#include <cstdint>

#include <vector>
#include <unordered_map>

class Day06 final
    : public Day
{
    struct Segment
    {
        int pos1;
        int pos2;
    };

    std::unordered_map<int, std::vector<int>> m_wallsX;
    std::unordered_map<int, std::vector<int>> m_wallsY;

    std::vector<Segment> m_segmentsHorizontal;
    std::vector<Segment> m_segmentsVertical;

    std::vector<uint8_t> m_buffer;

public:
    Day06();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
