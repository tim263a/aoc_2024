#pragma once

#include "days/day.h"

#include <cstdint>

#include <string>
#include <vector>

class Day19 final
    : public Day
{
    std::vector<uint8_t> m_buffer;

    std::vector<std::string> m_components;
    std::vector<std::string> m_targets;

public:
    Day19();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
