#include "days/day09.h"

#include <cassert>
#include <cstddef>

#include <array>
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
        if (i % 2 == 0)
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
                    .length = length,
                    .overrideIdx = (std::size_t) -1
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

uint64_t Day09::allocate(int value, int required, int origPosition)
{
    CandidateSpace& gap = m_nextGaps[required];
    std::size_t position = gap.position;

    if (position == -1 ||
        position >= origPosition)
    {
        // According to invariant, there is no gap that the file fits in.
        // Or the file would be after its original position, which prevents moves.

        printFmt("No gap for {} @ {}\n", required, origPosition);

        // Caller must later add stretchsum, because offset is not yet known.
        return -1;

        // Return stretchsum for unmoved file.
        // return getStretchSum(value, origPosition, value);
    }

    printFmt("Found gap for {} @ {} {} {} \n",
        required, gap.position, gap.offset, gap.length);

    int length = gap.length;
    if (required == length)
    {
        printFmt("Allocate complete {}\n", gap.position);
        advance(required, std::nullopt, origPosition);

        return getStretchSum(value, gap.offset, length);
    }
    else
    {
        assert(required < length);

        printFmt("Allocate {} out of {} @ {} {} {}\n",
            required, length, gap.position, gap.offset, gap.length);

        // Suballocate and add/ammend space override.
        SpaceOverride override {
            .position = position,
            .offset = gap.offset + required,
            .reducedLength = length - required,
        };

        if (gap.overrideIdx == -1)
        {
            m_overrides.push_back(override);
            gap.overrideIdx = m_overrides.size() - 1;

            printFmt("Override {} @ {} with {} {} {}\n",
                gap.overrideIdx, position,
                override.position, override.offset, override.reducedLength);
        }
        else
        {
            // Handle case where gap was already pointing to override.
            m_overrides[gap.overrideIdx] = override;

            printFmt("Ammend override {} @ {} to {} {} {}\n",
                gap.overrideIdx, position,
                override.position, override.offset, override.reducedLength);
        }

        // TODO: Make nextGaps point to part after suballocation.
        advance(length, override, origPosition);
    }

    // TODO: Calculate the stretchsum that results from moving the file.
    return 0;
}

void Day09::advance(int required, std::optional<SpaceOverride> override, int end)
{
    const CandidateSpace& gap = m_nextGaps[required];

    int minMovable = required;

    if (!override)
    {
        for (int i = required; i > 0; i--)
        {
            if (m_nextGaps[i].position == gap.position)
            {
                minMovable = i;
            }
        }
    }
    else
    {
        minMovable = override->reducedLength + 1;
    }

    printFmt("Min Movable {}\n", minMovable);

    int offset = gap.offset + gap.length;

    // TODO: Consider that current gap might have been overriden.

    // Note: Whatever happened, only gaps <= required must be adjusted,
    // because other gaps wouldn't have fit modified gap anyway.
    // Addendum: Incorrect, by override large gaps might have become small.
    // Fixed note: Only gaps <= original gap length must be adjusted.
    int originalGapLength = gap.length;

    int largestFound = minMovable - 1;

    for (std::size_t i = gap.position + 1; i < m_buffer.size() && i < end; offset += m_buffer[i] - '0', i++)
    {
        if (i % 2 == 0)
        {
            continue;
        }

        auto length = m_buffer[i] - '0';
        std::size_t overrideIdx = -1;

        // Search override to potentially reduce length.
        // TODO: Improve loop by somehow making m_overrides sorted?
        for (std::size_t j = 0; j < m_overrides.size(); j++)
        {
            auto& override = m_overrides[j];

            if (override.position == j)
            {
                length = override.reducedLength;
                offset = override.offset;
                overrideIdx = j;
                break; // m_override should only have one entry per position.
            }
        }

        if (length > largestFound)
        {
            for (std::size_t j = largestFound + 1; j <= length; j++)
            {
                m_nextGaps[j] = {
                    .position = i,
                    .offset = offset,
                    .length = length,
                    .overrideIdx = overrideIdx
                };

                printFmt("Advance gap {} @ {} {} {}\n", j, i, offset, length);
            }

            largestFound = length;

            if (largestFound >= originalGapLength)
            {
                return;
            }
        }
    }

    for (std::size_t j = largestFound + 1; j <= originalGapLength; j++)
    {
        m_nextGaps[j] = {
            .position = (std::size_t) -1,
            .offset = -1,
            .length = -1,
            .overrideIdx = (std::size_t) -1
        };

        printFmt("No more gap for {} before end @ {}\n", j, end);
    }
}

uint64_t Day09::calculatePart2()
{
    uint64_t sum = 0;

    m_buffer.resize(m_buffer.size() - 2); // Throw out trailing whitespace and zero.
    printFmt("Buffer resized to {}\n", m_buffer.size());

    m_nextGaps.fill({
        .position = (std::size_t) -1,
        .offset = -1,
        .length = -1
    }); // Indicate that there are no such gaps yet.
    initNextGaps(); // Starts invariant the nextGaps point to next gaps.

    // Reasonably adjust nextGaps;
    // TODO: Go from back to front, searching a space each time.
        // When finding something, update nextGaps.
    // TODO: Count unmoved files at end.

    std::size_t iBack = m_buffer.size() - 1;

    iBack -= (iBack) % 2; // Ensure iBack is even, i.e. it points to a file.
    int vBack = iBack / 2;

    printFmt("Back: {} -> {:c} (value {})\n", iBack, m_buffer[iBack], vBack);

    while (iBack > m_nextGaps[1].position)
    {
        uint64_t movedSum = allocate(vBack, m_buffer[iBack] - '0', iBack);
        if (movedSum != -1)
        {
            // File got moved.
            printFmt("Moved sum for {}: {}\n", vBack, movedSum);
            sum += movedSum;
        }
        else
        {
            printFmt("Not moving {} @ {}\n", vBack, iBack);
            m_notMovedFor2.push_back(iBack);
        }

        iBack -= 2;
        vBack -= 1;
    }

    printFmt("Not moving all before {} @ {}\n", vBack, iBack);

    printFmt("Not moved ({}):\n", m_notMovedFor2.size());
    for (auto notMoved : m_notMovedFor2)
    {
        // TODO: Add stretchSums for all number after last applied move.
        printFmt("{} -> {}\n", notMoved, 0);
    }

    return sum;
}
