#include "days/day04.h"

#include "util/print_fmt.h"
#include "util/read_input.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <string_view>

Day04::Day04() = default;

void Day04::parseInput()
{
    read_stdio_into_buffer(m_buffer);
}

int_fast16_t rowIdx = 0;
int_fast16_t columnIdx = 0;

static void checkOrReset(
    decltype(42) checkIdx,
    char currentChar, std::string_view target,
    int_fast16_t& runlength, uint64_t& counter)
{
    if (currentChar == target[runlength])
    {
        runlength += 1;
    }
    else if (currentChar == target[0])
    {
        runlength = 1;
    }
    else
    {
        runlength = 0;
    }

    if (runlength == 4)
    {
        printFmt("{} row {} column {}\n", checkIdx, rowIdx, columnIdx);

        counter += 1;
        runlength = 0;
    }
}

constexpr std::string_view FORWARDS = "XMAS";
constexpr std::string_view BACKWARDS = "SAMX";

uint64_t Day04::calculatePart1()
{
    printFmt("Read {} characters\n", m_buffer.size());
    uint64_t sum = 0;

    std::size_t lineLength = 0;

    auto it = m_buffer.begin();
    for (; *it != '\n'; it++, lineLength++) { }

    printFmt("Line Length {}\n", lineLength);

    // Runlengths of:
    // 1 - down left
    // 2 - up right -> backwards
    // 3 - down
    // 4 - up -> backwards
    // 5 - down right
    // 6 - up left -> backwards
    std::array<std::vector<int_fast16_t>, 6> runlengths;
    for (auto& v : runlengths)
    {
        v.resize(lineLength);
    }
    int_fast16_t runLengthForwards = 0;
    int_fast16_t runLengthBackwards = 0;

    std::array<std::size_t, 6> shifts;
    shifts.fill(4 * lineLength); // make modulo positive

    std::size_t lineIdx = 0;
    std::size_t idx = 0;
    for (it = m_buffer.begin(); it != m_buffer.end(); it++, idx++)
    {
        bool invalidChar = false;

        switch (*it)
        {
            case 'X':
            case 'M':
            case 'A':
            case 'S':
                break;

            case '\n':
                lineIdx++;
                idx = -1;

                runLengthForwards = 0;
                runLengthBackwards = 0;
                shifts[0] += 1;
                shifts[1] += 1;
                shifts[4] -= 1;
                shifts[5] -= 1;
                break;

            default:
                invalidChar = true;
                continue;
        }

        std::array<int_fast16_t*, 6> shifted;
        for (std::size_t i = 0; i < shifted.size(); i++)
        {
            shifted[i] = &runlengths[i].at((idx + shifts[i]) % lineLength);
            if (invalidChar)
            {
                *shifted[i] = 0;
            }
        }

        if (invalidChar)
        {
            continue;
        }

        rowIdx = lineIdx;
        columnIdx = idx;

        checkOrReset(0, *it, FORWARDS, runLengthForwards, sum);
        checkOrReset(1, *it, BACKWARDS, runLengthBackwards, sum);
        checkOrReset(2, *it, FORWARDS, *shifted[0], sum);
        checkOrReset(3, *it, BACKWARDS, *shifted[1], sum);
        checkOrReset(4, *it, FORWARDS, *shifted[2], sum);
        checkOrReset(5, *it, BACKWARDS, *shifted[3], sum);
        checkOrReset(6, *it, FORWARDS, *shifted[4], sum);
        checkOrReset(7, *it, BACKWARDS, *shifted[5], sum);
    }

    return sum;
}

uint64_t Day04::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
