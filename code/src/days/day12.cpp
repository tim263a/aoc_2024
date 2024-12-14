#include "days/day12.h"

#include "util/print_fmt.h"
#include "util/read_input.h"
#include <cstddef>

Day12::Day12()
    : m_buffer(32000)
{

}

void Day12::parseInput()
{
    read_stdio_into_buffer(m_buffer);
}

uint64_t Day12::calculatePart1()
{
    uint64_t sum = 0;

    struct Plot
    {
        int64_t area = 0;
        int64_t perimeter = 0;

        std::size_t mergedInto = 0; // 0 means not merged.
    };

    struct Stretch
    {
        int64_t start;
        int64_t end;

        uint8_t charType;
        std::size_t plotIdx;
    };

    std::vector<Plot> plots;

    std::vector<Stretch> prevLine;
    std::vector<Stretch> line;

    Stretch stretch {};

    for (auto it = m_buffer.cbegin(); it != m_buffer.cend(); it++)
    {
        if (*it == '\n')
        {
            // TODO: Add up all plots that do not have current representation.

            prevLine = std::move(line);
            line.clear();

            if (it[1] == '\n')
            {
                break;
            }

            stretch = {
                .start = 0,
                .end = 0,
                .charType = it[1],
                .plotIdx = 0
            };
        }

        if (*it != stretch.charType)
        {
            // Handle stop of current stretch.
            // Create new stretch.
        }

        // Check whether current charType matches the one from previous line.


    }

    return sum;
}

uint64_t Day12::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
