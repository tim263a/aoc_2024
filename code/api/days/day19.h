#pragma once

#include "days/day.h"

#include <cstdint>

#include <array>
#include <memory>
#include <string>
#include <vector>

class Day19 final
    : public Day
{
    struct Node
    {
        bool isValid = false;
        std::array<std::unique_ptr<Node>, 5> subNodes {};
    };

    std::vector<uint8_t> m_buffer;

    std::vector<std::string> m_components;
    std::vector<std::string> m_targets;

    uint64_t m_part2 = 0;

    void printTree(const Node& node, std::size_t idx, uint8_t indent,
        const std::string& prefix = "");
    void doSomethingRecursively(
        const std::vector<std::vector<uint8_t>>& letterLengths,
        uint64_t start);

public:
    Day19();

    void parseInput() override;

    uint64_t calculatePart1() override;
    uint64_t calculatePart2() override;
};
