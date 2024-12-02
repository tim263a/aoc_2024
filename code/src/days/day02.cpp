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

static int8_t signum(int8_t v)
{
    return v == 0 ? 0 : (std::signbit(v) ? -1 : 1);
}

uint64_t Day02::calculatePart1()
{
    debugFmt("Read {:d} lines\n", m_lines.size());

    uint64_t sum = 0;

    for (std::string& line : m_lines)
    {
        std::stringstream ss(line);

        std::optional<int8_t> lineSignum;
        int32_t prev = 0;
        int32_t now = 0;

        bool fail = false;

        ss >> prev;

        while (ss >> now)
        {
            int32_t diff = now - prev;
            uint32_t abs = std::abs(diff);
            debugFmt("({:d} {:d})", now, diff);
            if (!lineSignum)
            {
                lineSignum = signum(diff);
            }
            else if (*lineSignum != signum(diff))
            {
                fail = true;
            }

            if (abs < 1 || abs > 3)
            {
                fail = true;
            }

            prev = now;
        }

        debugFmt(" --> {}\n", !fail);

        if (!fail)
        {
            sum += 1;
        }
    }

    return sum;
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
            debugFmt("Added diff {} -> {}\n", diffs[i - 1], diff);
        }

        uint8_t abs = std::abs(diff);
        if (abs < 1 || abs > 3)
        {
            debugFmt("{:+d} D1 {} {}\n", skipIndex, i, diff);
            return false;
        }

        if (!requiredSignbit)
        {
            requiredSignbit = std::signbit(diff);
        }
        else if (requiredSignbit && std::signbit(diff) != *requiredSignbit)
        {
            debugFmt("{:+d} D2 {}\n", skipIndex, i, diff);
            return false;
        }
    }

    debugFmt("Valid (?)\n");
    return true;
}

uint64_t Day02::calculatePart2()
{
    debugFmt("Read {:d} diff lines\n", m_diffs.size());

    uint64_t sum = 0;

    for (int32_t j = 0; j < m_diffs.size(); j++)
    {
        const auto& lineDiffs = m_diffs[j];

        debugFmt("--- line {} ----- \n", j);
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
