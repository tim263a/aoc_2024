#pragma once

#include "days/day.h"

#include <cstdint>

#include <vector>

class Day01 final
    : public Day
{
    std::vector<uint32_t> l1;
    std::vector<uint32_t> l2;

public:
    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
