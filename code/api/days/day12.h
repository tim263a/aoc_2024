#pragma once

#include "days/day.h"

#include <cstdint>

class Day12 final
    : public Day
{

public:
    Day12();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
