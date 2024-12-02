#pragma once

#include "days/day.h"

#include <cstdint>

#include <string>
#include <vector>

class Day02 final
    : public Day
{
    std::vector<std::string> m_lines;

public:
    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
