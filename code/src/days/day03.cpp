#include "days/day03.h"

#include <cstdint>
#include <cstring>

#include "util/print_fmt.h"
#include "util/read_input.h"

Day03::Day03()
    : m_buffer(42000, 0)
    , m_part2(0)
{
}

void Day03::parseInput()
{
    read_stdio_into_buffer(m_buffer);
}

static int_fast16_t getNumber(
    uint8_t* ptr, uint_fast8_t& j, char delim, bool& foundDelim, bool& error)
{
    int_fast16_t operand = 0;

    j = 0;
    for (; j < 3; j++)
    {
        uint8_t c = ptr[j];

        if (c == delim)
        {
            foundDelim = true;
            break;
        }

        if (c < '0' || c > '9')
        {
            error = true;
            break;
        }

        operand *= 10;
        operand += c - '0';
    }

    return operand;
}

uint64_t Day03::calculatePart1()
{
    debugFmt("Read {} characters\n", m_buffer.size());
    uint64_t sum = 0;

    bool enabled = true;

    for (uint_fast32_t i = 0; i < m_buffer.size(); i++)
    {
        uint8_t* ptr = m_buffer.data() + i;

        if (ptr[0] == '\n')
        {
            debugFmt("\n\n");
            continue;
        }

        if (!strncmp((char*) ptr, "don't()", 7))
        {
            enabled = false;
        }
        else if (!strncmp((char*) ptr, "do()", 4))
        {
            enabled = true;
        }

        if (ptr[0] != 'm' ||
            ptr[1] != 'u' ||
            ptr[2] != 'l' ||
            ptr[3] != '(')
        {
            continue;
        }

        ptr += 4;

        bool foundDelim = false;
        bool error = false;
        uint_fast8_t j = 0;
        int_fast16_t operand1 = getNumber(ptr, j, ',', foundDelim, error);

        // debugFmt("operand1 for {}: {} foundComma {}\n", i, operand1, foundDelim);

        if (error || (!foundDelim && j != 3))
        {
            // debugFmt("D1 {}\n", error);
            continue;
        }

        if (ptr[j] != ',')
        {
            // debugFmt("D2\n");
            continue;
        }

        ptr += j + 1;

        int_fast16_t operand2 = getNumber(ptr, j, ')', foundDelim, error);

        // debugFmt("operand2 for {}: {} foundDelim {}\n", i, operand2, foundDelim);

        if (error || (!foundDelim && j != 3))
        {
            continue;
        }

        if (ptr[j] != ')')
        {
            continue;
        }

        debugFmt("mul({},{})", operand1, operand2);

        sum += operand1 * operand2;
        m_part2 += enabled * operand1 * operand2;
    }

    return sum;
}

uint64_t Day03::calculatePart2()
{
    return m_part2;
}
