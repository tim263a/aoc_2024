#include "days/day09.h"

#include <cassert>
#include <cstddef>

#include <array>
#include <iterator>
#include <limits>
#include <vector>

#include "util/print_fmt.h"
#include "util/read_input.h"

Day09::Day09()
    : m_buffer(32000)
{

}

void Day09::parseInput()
{
    read_stdio_into_buffer(m_buffer);
}

constinit int stretchSums[10] = {
    0, // 0
    1, // 1
    3, // 2
    6, // 3
    10, // 4
    15, // 5
    21, // 6
    28, // 7
    36, // 8
    45, // 9
};

static inline uint64_t getStretchSum(
    uint64_t value, uint64_t start, uint64_t range)
{
    if (!range) [[unlikely]]
    {
        return 0;
    }

    return (stretchSums[range - 1] + (start) * range) * value;
}

uint64_t Day09::calculatePart1()
{
    uint64_t sum = 0;

    std::size_t iFront = 0;
    std::size_t iBack = m_buffer.size() - 3; // TODO: Make sure this points to the last space.

    iBack -= (iBack) % 2; // Ensure iBack is even, i.e. it points to a file.
    int vBack = iBack / 2;
    int leftToMove = m_buffer[iBack] - '0'; // length left of file to move

    printFmt("Front: {} -> {:c}\n", iFront, m_buffer[iFront]);
    printFmt("Back: {} -> {:c} (value {})\n", iBack, m_buffer[iBack], vBack);

    int value = 0; // File index of current file.
    int offset = 0; // Sum of lengths so far.

    for (; iFront < iBack; iFront += 2, value++)
    {
        int l0 = m_buffer[iFront] - '0'; // file length
        int l1 = m_buffer[iFront + 1] - '0'; // space length

        int offset0 = offset;
        int offset1 = offset0 + l0;

        uint64_t stretchSum0 = getStretchSum(value, offset, l0);
        printFmt("Keep {} at (value {}, offset {}, length {}) -> {}\n",
            value, value, offset, l0, stretchSum0);
        sum += stretchSum0;

        int spaceLeft = l1;
        while (spaceLeft > 0)
        {
            if (spaceLeft >= leftToMove) // file can be moved completely
            {
                uint64_t stretchSum1 = getStretchSum(vBack, offset1, leftToMove);
                printFmt("Move {} into (value {}, offset {}, length {}) -> {}\n",
                    iBack, vBack, offset1, leftToMove, stretchSum1);
                sum += stretchSum1;

                offset1 += leftToMove;
                spaceLeft -= leftToMove;

                // Select next file to move.
                iBack -= 2;
                vBack -= 1;
                leftToMove = m_buffer[iBack] - '0';

                if (iFront >= iBack)
                {
                    break;
                }
            }
            else // File needs to be split up.
            {
                uint64_t stretchSum1 = getStretchSum(vBack, offset1, spaceLeft);
                printFmt("Fill {} into (value {}, offset {}, length {}) -> {}\n",
                    iBack, vBack, offset1, spaceLeft, stretchSum1);
                sum += stretchSum1;

                // Keep same file to move.
                leftToMove -= spaceLeft;
                break;
            }
        }

        offset += l0 + l1;
    }

    if (iFront == iBack)
    {
        uint64_t stretchSumLeft = getStretchSum(vBack, offset, leftToMove);
        printFmt("Count partial left {} into (value {}, offset {}, length {}) -> {}\n",
            iBack, vBack, offset, leftToMove, stretchSumLeft);
        sum += stretchSumLeft;
    }

    return sum;
}

void Day09::initNextGaps()
{
    int largestFound = 0;

    int offset = 0;

    for (std::size_t i = 0; i < m_buffer.size(); offset += m_buffer[i] - '0', i++)
    {
        if (i % 2)
        {
            continue;
        }

        auto length = m_buffer[i] - '0';

        if (length > largestFound)
        {
            for (std::size_t j = largestFound + 1; j <= length; j++)
            {
                m_nextGaps[j] = {
                    .position = i,
                    .offset = offset,
                    .length = length
                };

                printFmt("Registered gap {} @ {} {} {}\n", j, i, offset, length);
            }

            largestFound = length;

            if (largestFound == 9)
            {
                return;
            }
        }
    }
}

void Day09::allocate(int required, int end)
{
    const CandidateSpace& gap = m_nextGaps[required];
    std::size_t position = gap.position;

    if (position == std::numeric_limits<std::size_t>::max())
    {
        // According to invariant, there is no gap that the file fits in.

        // TODO: Add stretchsum for unmoved file - or have caller do it.
        return;
    }

    int length = gap.length;
    if (required == length)
    {
        advance(required, end);
    }
    else
    {
        assert(required < length);

        // TODO: Handle case where gap was already pointing to override.

        // Suballocate and add space override.
        m_overrides.push_back({
            .position = position,
            .offset = gap.offset + required,
            .reducedLength = length - required,
        });

        // TODO: Make nextGaps p[oint to part after suballocation.

        advance(length, end);
    }

    // TODO: Calculate the stretchsum that results from moving the file.
}

void Day09::advance(int required, int end)
{
    const CandidateSpace& gap = m_nextGaps[required];

    int largestFound = required;

    int offset = gap.offset;

    for (std::size_t i = gap.position + 2; i < m_buffer.size() && i < end; offset += m_buffer[i] - '0', i++)
    {
        if (i % 2)
        {
            continue;
        }

        auto length = m_buffer[i] - '0';

        // TODO: Search override to potentially reduce length.

        if (length > largestFound)
        {
            for (std::size_t j = largestFound + 1; j <= length; j++)
            {
                m_nextGaps[j] = {
                    .position = i,
                    .offset = offset,
                    .length = length
                };

                printFmt("Advanced gap {} @ {} {} {}\n", j, i, offset, length);
            }

            largestFound = length;

            if (largestFound == 9)
            {
                return;
            }
        }
    }
}

uint64_t Day09::calculatePart2()
{
    uint64_t sum = 0;

    m_buffer.resize(m_buffer.size() - 2); // Throw out trailing whitespace and zero.
    printFmt("Buffer resized to {}\n", m_buffer.size());

    m_nextGaps.fill({
        .position = std::numeric_limits<std::size_t>::max(),
        .offset = -1,
        .length = -1
    }); // Indicate that there are no such gaps yet.
    initNextGaps(); // Starts invariant the nextGaps point to next gaps.

    return sum;

    // Reasonably adjust nextGaps;
    // TODO: Go from back to front, searching a space each time.
        // When finding something, update nextGaps.
    // TODO: Count unmoved files at end.

    std::size_t iFront = 0;
    std::size_t iBack = m_buffer.size() - 3; // TODO: Make sure this points to the last space.

    iBack -= (iBack) % 2; // Ensure iBack is even, i.e. it points to a file.
    int vBack = iBack / 2;
    int leftToMove = m_buffer[iBack] - '0'; // length left of file to move

    printFmt("Front: {} -> {:c}\n", iFront, m_buffer[iFront]);
    printFmt("Back: {} -> {:c} (value {})\n", iBack, m_buffer[iBack], vBack);

    int value = 0; // File index of current file.
    int offset = 0; // Sum of lengths so far.

    for (; iFront < iBack; iFront += 2, value++)
    {
        int l0 = m_buffer[iFront] - '0'; // file length
        int l1 = m_buffer[iFront + 1] - '0'; // space length

        int offset0 = offset;
        int offset1 = offset0 + l0;

        uint64_t stretchSum0 = getStretchSum(value, offset, l0);
        printFmt("Keep {} at (value {}, offset {}, length {}) -> {}\n",
            value, value, offset, l0, stretchSum0);
        sum += stretchSum0;

        int spaceLeft = l1;
        while (spaceLeft > 0)
        {
            if (spaceLeft >= leftToMove) // file can be moved completely
            {
                uint64_t stretchSum1 = getStretchSum(vBack, offset1, leftToMove);
                printFmt("Move {} into (value {}, offset {}, length {}) -> {}\n",
                    iBack, vBack, offset1, leftToMove, stretchSum1);
                sum += stretchSum1;

                offset1 += leftToMove;
                spaceLeft -= leftToMove;

                // Select next file to move.
                iBack -= 2;
                vBack -= 1;
                leftToMove = m_buffer[iBack] - '0';

                if (iFront >= iBack)
                {
                    break;
                }
            }
            else // File needs to be split up.
            {
                uint64_t stretchSum1 = getStretchSum(vBack, offset1, spaceLeft);
                printFmt("Fill {} into (value {}, offset {}, length {}) -> {}\n",
                    iBack, vBack, offset1, spaceLeft, stretchSum1);
                sum += stretchSum1;

                // Keep same file to move.
                leftToMove -= spaceLeft;
                break;
            }
        }

        offset += l0 + l1;
    }

    if (iFront == iBack)
    {
        uint64_t stretchSumLeft = getStretchSum(vBack, offset, leftToMove);
        printFmt("Count partial left {} into (value {}, offset {}, length {}) -> {}\n",
            iBack, vBack, offset, leftToMove, stretchSumLeft);
        sum += stretchSumLeft;
    }

    return sum;
}
