#include "days/day17.h"

#include "util/print_fmt.h"
#include "util/read_input.h"

Day17::Day17()
    : m_buffer(256)
{

}

template<typename Iter>
static uint64_t readNumber(Iter& it)
{
    uint64_t number = 0;

    for (; *it >= '0' && *it <= '9'; it++)
    {
        number *= 10;
        number += *it - '0';
    }

    return number;
}


void Day17::parseInput()
{
    read_stdio_into_buffer(m_buffer);

    auto it = m_buffer.cbegin();

    it += 12;
    m_regA = readNumber(it);
    it += 13;
    m_regB = readNumber(it);
    it += 13;
    m_regC = readNumber(it);

    it += 11;
    for (; *it != '\0'; it += 2)
    {
        m_opCodes.push_back(*it -  '0');
    }
}

uint64_t Day17::calculatePart1()
{
    uint64_t sum = 0;

    return sum;
}

uint64_t Day17::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
