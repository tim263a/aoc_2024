#include "days/day11.h"

#include "util/print_fmt.h"
#include "util/read_input.h"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream>

Day11::Day11()
    : m_buffer(100)
{
}

void Day11::parseInput()
{
    read_stdio_into_buffer(m_buffer);

    std::string inputString(m_buffer.cbegin(), m_buffer.cend());
    std::stringstream stream(inputString);

    int number = 0;
    while (stream >> number) {
        m_inputNumbers.push_back(number);
    }
}

static bool splitEven(uint64_t v, uint64_t& left, uint64_t& right)
{
    uint64_t numberLength = 0;
    for (uint64_t shifted = 1; v >= shifted; numberLength++, shifted *= 10) { }

    DEBUG_FMT("NumberLength {}: {}\n", v, numberLength);

    if (numberLength % 2)
    {
        return false;
    }

    left = v;
    right = 0;

    uint64_t rightShift = 1;

    for (uint64_t i = 0; i < numberLength / 2; i++)
    {
        right += (left % 10) * rightShift;
        rightShift *= 10;
        left /= 10;
    }

    DEBUG_FMT("Split {} -> {} {}\n", v, left, right);

    return true;
}

uint64_t Day11::calculatePart1()
{
    uint64_t sum = 0;

    std::vector<uint64_t> v0 = m_inputNumbers;
    std::vector<uint64_t> v1;

    for (int i = 0; i < 25; i++)
    {
        for (uint64_t v : v0)
        {
            uint64_t left = 0;
            uint64_t right = 0;

            if (v == 0)
            {
                v1.push_back(1);
            }
            else if (splitEven(v, left, right))
            {
                v1.push_back(left);
                v1.push_back(right);
            }
            else
            {
                v1.push_back(2024 * v);
            }
        }

#if 0
        for (uint64_t v : v1)
        {
            printFmt("{} ", v);
        }
        printFmt("\n");
#endif

        sum = v1.size();
        printFmt("Iteration {}: {}\n", i, sum);

        std::swap(v0, v1);
        v1.clear();
    }

    return sum;
}

void Day11::cache(uint64_t value, int64_t cyclesLeft, uint64_t result)
{
    if (value < 10000)
    {
        return;
    }

    auto vec = m_lengthMap[value];
    vec.resize(cyclesLeft, std::max<std::size_t>(cyclesLeft, vec.size()));
    vec[cyclesLeft - 1] = result;
}

static uint64_t requests = 0;
static uint64_t found = 0;

uint64_t Day11::findResultLength(uint64_t value, int64_t cyclesLeft)
{
    if (cyclesLeft <= 0)
    {
        return 1;
    }

    if (value == 0)
    {
        return findResultLength(1, cyclesLeft - 1);
    }

    if (value < 1000)
    {
        requests += 1;

        if (requests % 1000)
        {
            printFmt("Hit rate {}/{}\n", found, requests);
        }

        auto mapping = m_lengthMap.find(value);
        if (mapping != m_lengthMap.end() &&
            mapping->second.size() >= cyclesLeft)
        {
            uint64_t hashed = mapping->second[cyclesLeft];
            if (hashed)
            {
                found += 1;
                return hashed;
            }
        }
    }

    uint64_t left = 0;
    uint64_t right = 0;

    assert(value != 0);

    if (splitEven(value, left, right))
    {
        uint64_t resLeft = findResultLength(left, cyclesLeft - 1);
        cache(left, cyclesLeft, resLeft);

        uint64_t resRight = findResultLength(right, cyclesLeft - 1);
        cache(right, cyclesLeft, resRight);

        return resLeft + resRight;
    }
    else
    {
        return findResultLength(2024 * value, cyclesLeft - 1);
    }
}

uint64_t Day11::calculatePart2()
{
    uint64_t sum = 0;

    for (uint64_t number : m_inputNumbers)
    {
        sum += findResultLength(number, 25);
    }

    return sum;
}
