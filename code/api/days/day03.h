#pragma once

#include "days/day.h"

#include <cstdint>

class Day03 final
    : public Day
{

public:
    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
