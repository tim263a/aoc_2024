#include "days/day19.h"

#include <algorithm>
#include <cstddef>

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

void normalizeString(std::string& str)
{
    for (auto& c : str)
    {
        switch (c)
        {
            case 'w':
                c = 'a';
            break;
            case 'u':
                c = 'b';
            break;
            case 'b':
                c = 'c';
            break;
            case 'r':
                c = 'd';
            break;
            case 'g':
                c = 'e';
            break;
            default:
                c = '0';
            break;
        }
    }
}

uint64_t Day19::calculatePart1()
{
    uint64_t sum = 0;

#if 0 // Print 'normalized' input (i.e. input mapped to 'a'-'e'.
    for (std::size_t i = 0; i < m_components.size(); i++)
    {
        auto& component = m_components[i];
        normalizeString(component);

        printFmt("{}", component);
        if (i != m_components.size() - 1)
        {
            printFmt(", ");
        }
    }

    printFmt("\n\n");

    for (std::size_t i = 0; i < m_targets.size(); i++)
    {
        auto& target = m_targets[i];
        normalizeString(target);

        printFmt("{}", target);
        printFmt("\n");
    }
#endif

#if 0
    std::sort(m_components.begin(), m_components.end());
    printFmt("Sorted components ({}):\n", m_components.size());
    for (std::string component : m_components)
    {
        printFmt("{}\n", component);
    }
#endif

    return sum;
}

uint64_t Day19::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
