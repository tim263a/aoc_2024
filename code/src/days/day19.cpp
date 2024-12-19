#include "days/day19.h"

#include "util/print_fmt.h"
#include "util/read_input.h"

Day19::Day19()
    : m_buffer(32000)
{

}

template<typename Iter>
static std::string readString(Iter& it)
{
    auto itBegin = it;
    while (*it >= 'a' && *it <= 'z')
    {
        it++;
    }
    return { itBegin, it };
}

void Day19::parseInput()
{
    read_stdio_into_buffer(m_buffer);

    auto it = m_buffer.cbegin();
    while (*it != '\n')
    {
        if (*it == ',')
        {
            it += 2; // ", "
        }

        m_components.push_back(readString(it));
    }

    it += 2;

    while (*it != '\0')
    {
        m_targets.push_back(readString(it));
        it++;
    }
}

uint64_t Day19::calculatePart1()
{
    uint64_t sum = 0;

    return sum;
}

uint64_t Day19::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
