#include "days/day08.h"

#include "util/print_fmt.h"
#include "util/read_input.h"
#include <cstddef>

Day08::Day08()
{

}

void Day08::parseInput()
{
    read_stdio_into_buffer(m_buffer);
}

void Day08::addHash(int width, int x, int y)
{
    int hash = y * width + x;

    if (x < 0 || y < 0 || x >= width)
    {
        return;
    }

    m_hashes.insert(hash);
}

uint64_t Day08::calculatePart1()
{
    uint64_t sum = 0;

    int lineWidth = 0;

    int columnIdx = 0;
    int lineIdx = 0;

    for (auto it = m_buffer.cbegin(); it != m_buffer.cend(); it++, columnIdx++)
    {
        if (*it == '\n')
        {
            lineWidth = columnIdx;

            lineIdx++;
            columnIdx = -1;
            continue;
        }

        if (*it == '.')
        {
            continue;
        }

        m_positions[*it].emplace_back(lineIdx, columnIdx);
        printFmt("Station {:c} @ {}|{}\n", *it, lineIdx, columnIdx);
    }

    printFmt("lineWidth {}\n", lineWidth);

    for (auto entry : m_positions)
    {
        auto typePositions = entry.second;

        printFmt("Type {:c}: ", entry.first);
        for (auto pos : typePositions)
        {
            printFmt("{}|{} ", pos.first, pos.second);
        }
        printFmt("\n");

        for (std::size_t i = 0; i < typePositions.size(); i++)
        {
            for (std::size_t j = i + 1; j < typePositions.size(); j++)
            {
                int x1 = typePositions[i].first;
                int y1 = typePositions[i].second;
                int x2 = typePositions[j].first;
                int y2 = typePositions[j].second;

                int dX = x2 - x1;
                int dY = y2 - y1;

                int hX1 = x2 + dX;
                int hY1 = y2 + dY;

                int hX2 = x1 - dX;
                int hY2 = y1 - dY;

                addHash(lineWidth, hX1, hY1);
                addHash(lineWidth, hX2, hY2);

                printFmt("{}|{}|{}|{}-->", x1, y1, x2, y2);
                printFmt("{}|{},", hX1, hY1);
                printFmt("{}|{} ", hX2, hY2);
            }

            printFmt("\n");
        }
    }

    for (int i = 0; i < lineIdx; i++)
    {
        for (int j = 0; j < lineWidth; j++)
        {
            if (m_hashes.contains(j * lineWidth + i))
            {
                sum += 1;
                printFmt("#");
            }
            else
            {
                printFmt(".");
            }
        }
        printFmt("\n");
    }

    return sum;
}

uint64_t Day08::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
