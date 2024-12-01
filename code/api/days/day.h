#pragma once

#include <cstdint>

class Day
{
public:
    virtual void parseInput() = 0;

    virtual uint64_t calculatePart1() = 0;
    virtual uint64_t calculatePart2() = 0;
};
