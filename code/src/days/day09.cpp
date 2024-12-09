#include "days/day09.h"

#include <cstddef>

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

static inline int getStretchSum(int value, int start, int range)
{
    return (stretchSums[range] + (start - 1) * range) * value;
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

        int stretchSum0 = getStretchSum(value, offset, l0);
        printFmt("Keep {} at (value {}, offset {}, length {}) -> {}\n",
            value, value, offset, l0, stretchSum0);
        sum += stretchSum0;

        int spaceLeft = l1;
        while (spaceLeft > 0)
        {
            if (spaceLeft >= leftToMove) // file can be moved completely
            {
                int stretchSum1 = getStretchSum(vBack, offset1, leftToMove);
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
                int stretchSum1 = getStretchSum(vBack, offset1, spaceLeft);
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
        int stretchSumLeft = getStretchSum(vBack, offset, leftToMove);
        printFmt("Count partial left {} into (value {}, offset {}, length {}) -> {}\n",
            iBack, vBack, offset, leftToMove, stretchSumLeft);
        sum += stretchSumLeft;
    }

    return sum;
}

uint64_t Day09::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
