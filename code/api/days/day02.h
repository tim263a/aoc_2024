#pragma once

#include "days/day.h"

#include <cstdint>

#include <string>
#include <vector>

class Day02 final
    : public Day
{
    std::vector<std::string> m_lines;
    std::vector<std::vector<int8_t>> m_diffs;

public:
    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
