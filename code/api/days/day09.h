#pragma once

#include "days/day.h"

#include <cstdint>

#include <array>
#include <vector>

class Day09 final
    : public Day
{
    std::vector<uint8_t> m_buffer;

    // For Part 2

    struct CandidateSpace
    {
        std::size_t position;
        int offset;
        int length;
    };

    struct SpaceOverride
    {
        std::size_t position;
        int offset;
        int reducedLength;
    };

    std::array<CandidateSpace, 10> m_nextGaps;
    std::vector<SpaceOverride> m_overrides;

    void initNextGaps();
    void allocate(int length, int end);
    void advance(int required, int end);

public:
    Day09();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
