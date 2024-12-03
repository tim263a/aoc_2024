#include "days/day02.h"

#include <algorithm>
#include <cstdint>
#include <cmath>
#include <optional>
#include <sstream>
#include <utility>
#include <vector>

#include "util/print_fmt.h"
#include "util/read_input.h"

void Day02::parseInput()
{
    m_lines = read_stdin_lines();

    for (std::string& line : m_lines)
    {
        std::stringstream ss(line);

        int32_t now = 0;
        int32_t prev = 0;
        ss >> prev;

        std::vector<int8_t> diffs;

        while (ss >> now)
        {
            diffs.push_back(now - prev);
            prev = now;
        }

        m_diffs.emplace_back(std::move(diffs));
    }
}

static bool isValid(const std::vector<int8_t> diffs, int32_t skipIndex)
{
    std::optional<bool> requiredSignbit;

    int32_t nDiffs = diffs.size();

    bool skipStart = skipIndex == 0;
    bool skipEnd = skipIndex == nDiffs;

    for (int32_t i = skipStart; i < nDiffs - skipEnd; i++)
    {
        if (i + 1 == skipIndex)
        {
            continue;
        }

        int8_t diff = diffs[i];

        if (i == skipIndex)
        {
            diff += diffs[i - 1];
            DEBUG_FMT("Added diff {} -> {}\n", diffs[i - 1], diff);
        }

        uint8_t abs = std::abs(diff);
        if (abs < 1 || abs > 3)
        {
            DEBUG_FMT("{:+d} D1 {} {}\n", skipIndex, i, diff);
            return false;
        }

        if (!requiredSignbit)
        {
            requiredSignbit = std::signbit(diff);
        }
        else if (requiredSignbit && std::signbit(diff) != *requiredSignbit)
        {
            DEBUG_FMT("{:+d} D2 {}\n", skipIndex, i, diff);
            return false;
        }
    }

    DEBUG_FMT("Valid (?)\n");
    return true;
}

uint64_t Day02::calculatePart1()
{
    DEBUG_FMT("Read {:d} lines\n", m_diffs.size());

    uint64_t sum = 0;

    for (int32_t j = 0; j < m_diffs.size(); j++)
    {
        const auto& lineDiffs = m_diffs[j];

        sum += isValid(lineDiffs, -1);
    }

    return sum;
}

uint64_t Day02::calculatePart2()
{
    DEBUG_FMT("Read {:d} diff lines\n", m_diffs.size());

    uint64_t sum = 0;

    for (int32_t j = 0; j < m_diffs.size(); j++)
    {
        const auto& lineDiffs = m_diffs[j];

        DEBUG_FMT("--- line {} ----- \n", j);
        for (int32_t i = -1; i <= (int32_t) lineDiffs.size(); i++)
        {
            if (isValid(lineDiffs, i))
            {
                sum += 1;
                break;
            }
        }
    }

    return sum;
}
