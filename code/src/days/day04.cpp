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

static int_fast16_t checkOrReset(
    decltype(42) checkIdx,
    char currentChar, std::string_view target,
    int_fast16_t runlength, uint64_t& counter)
{
    int_fast16_t result = 0;

    if (currentChar == target[runlength])
    {
        result = runlength + 1;
    }
    else if (currentChar == target[0])
    {
        return 1;
    }
    else
    {
        return 0;
    }

    if (result == 4)
    {
        printFmt("{} row {} column {}\n", checkIdx, rowIdx, columnIdx);

        counter += 1;
        result = 0;
    }

    return result;
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
    // 0 - down right
    // 1 - up left -> backwards
    // 2 - down
    // 3 - up -> backwards
    // 4 - down left
    // 5 - up right -> backwards
    std::vector<std::array<int_fast16_t, 6>> runlengths(lineLength + 2, {{}});

    int_fast16_t runLengthForwards = 0;
    int_fast16_t runLengthBackwards = 0;

    std::size_t delayIdx = 0;
    std::array<int_fast16_t, 6> delayed {};
    std::size_t delayIdx2 = 0;
    std::array<int_fast16_t, 6> delayed2 {};

    std::size_t lineIdx = 1;
    std::size_t idx = 1;
    for (it = m_buffer.begin(); it != m_buffer.end(); it++, idx++)
    {
        rowIdx = lineIdx;
        columnIdx = idx;

        switch (*it)
        {
            case 'X':
            case 'M':
            case 'A':
            case 'S':
                runLengthForwards = checkOrReset(0, *it, FORWARDS, runLengthForwards, sum);
                runLengthBackwards = checkOrReset(1, *it, BACKWARDS, runLengthBackwards, sum);

                delayIdx = idx;
                delayed = {
                    checkOrReset(2, *it, FORWARDS, runlengths[idx + 1][0], sum),
                    checkOrReset(3, *it, BACKWARDS, runlengths[idx + 1][1], sum),
                    checkOrReset(4, *it, FORWARDS, runlengths[idx][2], sum),
                    checkOrReset(5, *it, BACKWARDS, runlengths[idx][3], sum),
                    checkOrReset(6, *it, FORWARDS, runlengths[idx - 1][4], sum),
                    checkOrReset(7, *it, BACKWARDS, runlengths[idx - 1][5], sum)
                };
                break;

            case '\n':
                lineIdx++;
                idx = 0; // So next iteration starts with 1.

                runLengthForwards = 0;
                runLengthBackwards = 0;

                // runlengths.begin()->fill(0);
                // runlengths.rbegin()->fill(0);
                break;

            default:
                runLengthForwards = 0;
                runLengthBackwards = 0;

                delayIdx = idx;
                delayed.fill(0);
                break;
        }

        runlengths[delayIdx2] = delayed2;
        delayIdx2 = delayIdx;
        delayed2 = delayed;
    }

    return sum;
}

uint64_t Day04::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
