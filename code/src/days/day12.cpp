#include "days/day12.h"

#include "util/print_fmt.h"
#include "util/read_input.h"
#include <cstddef>
#include <cstdint>

Day12::Day12()
    : m_buffer(32000)
    , m_width(0)
    , m_height(0)
{

}

void Day12::parseInput()
{
    read_stdio_into_buffer(m_buffer);

    for (auto it = m_buffer.cbegin(); *it != '\n'; it++, m_width++) { }
    m_height = m_buffer.size() / (m_width + 1); // consider '\n'

    printFmt("Map width {} height {}\n", m_width, m_height);
}

uint64_t Day12::calculatePart1()
{
    uint64_t sum = 0;

    struct CellState
    {
        uint64_t index;
        uint64_t lowlink;
        bool onStack;
    };

    uint64_t nextIndex = 1;

    std::vector<CellState> cellStates(m_width * m_height, {{}});

    for (std::size_t y = 0; y < m_height; y++)
    {
        for (std::size_t x = 0; x < m_height; x++)
        {
            std::size_t bufferIdx = y * (m_width + 1) + x; // with '\n'
            std::size_t stateIdx = y * m_width + x; // without '\n'

            uint8_t c = m_buffer[bufferIdx];
            CellState& v = cellStates[stateIdx];

            if (!v.index)
            {
                // connect()
            }
        }
    }

    return sum;
}

uint64_t Day12::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
