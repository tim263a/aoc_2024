#include "days/day15.h"

#include "util/print_fmt.h"
#include "util/read_input.h"
#include <cstddef>
#include <cstdint>
#include <iterator>

Day15::Day15()
    : m_buffer(32000)
{

}

void Day15::parseInput()
{
    read_stdio_into_buffer(m_buffer);

    m_width = 0;
    m_height = 0;

    int64_t i = 0;
    auto it = m_buffer.begin();
    for (;; i++, it++)
    {
        if (it[0] == '\n')
        {
            if (!m_width)
            {
                m_width = i;
            }
            m_height += 1;

            if (it[1] == '\n')
            {
                it += 2;
                break;
            }
        }
        else if (it[0] == '@') [[unlikely]]
        {
            m_startX = i % (m_width + 1);
            m_startY = m_height;

            it[0] = '.'; // Virtuallize roby so old instance isn't in the way.
        }
    }

    m_idxDirections = std::distance(m_buffer.begin(), it);

    printFmt("width {} height {}, startX {} startY {}\n",
        m_width, m_height, m_startX, m_startY);
}

uint8_t& Day15::mapAt(std::size_t x, std::size_t y)
{
    return m_buffer[y * (m_width + 1) + x];
}

uint64_t Day15::calculatePart1()
{
    uint64_t sum = 0;

    int64_t posX = m_startX;
    int64_t posY = m_startY;

    for (auto it = m_buffer.cbegin() + m_idxDirections; it != m_buffer.cend(); it++)
    {
        if (*it == '\n')
        {
            continue;
        }
        else if (*it == '\0')
        {
            break;
        }

        printFmt("{:c} --> ", *it);

        int64_t dX = 0;
        int64_t dY = 0;

        switch (*it)
        {
            case '>':
                dX = 1;
            break;
            case '<':
                dX = -1;
            break;
            case 'v':
                dY = 1;
            break;
            case '^':
                dY = -1;
            break;
            default:
            break;
        }

        int searchX = posX;
        int searchY = posY;

        int distance = 0;

        bool foundSpace = false;

        while (true)
        {
            searchX += dX;
            searchY += dY;

            auto v = mapAt(searchX, searchY);

            if (v == '.')
            {
                foundSpace = true;
                break;
            }
            else if (v == '#')
            {
                break;
            }

            distance++;
        }

        printFmt("Moving {} boxes {} {} {:+} {:+}\n", distance, posX, posY, dX, dY);

        if (foundSpace)
        {
            for (int i = distance + 1; i > 1; i--)
            {
                printFmt("Move {} {} {:c} to {} {} {:c}\n", 
                    posX + (i - 1) * dX, posY + (i - 1) * dY,
                    mapAt(posX + (i - 1) * dX, posY + (i - 1) * dY),
                    posX + i * dX, posY + i * dY,
                    mapAt(posX + i * dX, posY + i * dY));

                mapAt(posX + i * dX, posY + i * dY) =
                    mapAt(posX + (i - 1) * dX, posY + (i - 1) * dY);
            }

            posX += dX;
            posY += dY;

            mapAt(posX, posY) = '.';
        }
    }

    for (std::size_t y = 0; y < m_height; y++)
    {
        for (std::size_t x = 0; x < m_width; x++)
        {
            auto v = mapAt(x, y);
            printFmt("{:c}", v);
            if (v == 'O')
            {
                sum += 100 * y + x;
            }
        }

        printFmt("\n");
    }

    return sum;
}

uint64_t Day15::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
