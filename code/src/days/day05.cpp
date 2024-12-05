#include "days/day05.h"

#include "util/print_fmt.h"
#include "util/read_input.h"
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <vector>

Day05::Day05() = default;

static inline char number(char c)
{
    return c - '0';
}

void Day05::parseInput()
{
    read_stdio_into_buffer(m_buffer);

    int nRules = 0;

    auto it = m_buffer.cbegin();
    for (; it != m_buffer.cend(); it += 6, nRules += 1)
    {
        if (*it == '\n')
        {
            break;
        }

        auto n0 = 10 * number(it[0]) + number(it[1]);
        auto n1 = 10 * number(it[3]) + number(it[4]);

        // printFmt("{} {}\n", n0, n1);

        m_ordering[n1].push_back(n0);
    }

    printFmt("Found {} rules\n", nRules);

    m_itUpdates = it + 1;
}

int Day05::orderAndQuery(const std::vector<int> lineNumbers)
{
    std::size_t nNumbers = lineNumbers.size();

    std::vector<std::vector<int>> dependencies;
    dependencies.resize(nNumbers);

    for (std::size_t i = 0; i < nNumbers; i++)
    {
        int iNumber = lineNumbers[i];
        DEBUG_FMT("Deps for {}: ", iNumber);

        const auto& ordering = m_ordering[iNumber];
        auto& deps = dependencies[i];

        for (std::size_t j = 0; j < nNumbers; j++)
        {
            if (i == j)
            {
                continue;
            }

            int jNumber = lineNumbers[j];
            if (std::find(ordering.cbegin(), ordering.cend(), jNumber) != ordering.cend())
            {
                deps.push_back(jNumber);
                DEBUG_FMT("{} ", jNumber);
            }
        }

        DEBUG_FMT("\n");
    }

    std::vector<int> ordered;

    while (ordered.size() <= nNumbers / 2)
    {
        std::size_t pickIdx = 0;
        int pick = 0;

        for (std::size_t i = 0; i < nNumbers; i++)
        {
            if (dependencies[i].empty())
            {
                pickIdx = i;
                pick = lineNumbers[i];

                DEBUG_FMT("Picked {}\n", pick);

                dependencies[i].push_back(100); // Prevent double picking.
            }
        }

        ordered.push_back(pick);

        for (std::size_t i = 0; i < nNumbers; i++)
        {
            std::erase(dependencies[i], pick);
        }
    }

    int queried = *ordered.rbegin();
    DEBUG_FMT("queried {}\n", queried);

    return queried;
}

uint64_t Day05::calculatePart1()
{
    uint64_t sum = 0;

    std::vector<int> rules;
    std::vector<int> lineNumbers;

    int numbersInLine = 0;
    int lineIdx = 0;
    bool invalid = false;

    for (auto it = m_itUpdates; it != m_buffer.cend(); it++)
    {
        if (*it == '\n')
        {
            if (!invalid)
            {
                auto itMiddle = it - (3 * (numbersInLine / 2) + 2);
                int middle = 10 * number(itMiddle[0]) + number(itMiddle[1]);

                DEBUG_FMT("valid {} rules {} numbers {} middle {}\n",
                    lineIdx, rules.size(), numbersInLine, middle);

                sum += middle;
            }
            else
            {
                auto itBegin = it - 3 * numbersInLine + 1;
                m_part2 += orderAndQuery(lineNumbers);
            }

            rules.clear();

            lineIdx++;
            invalid = false;
            numbersInLine = 0;
            lineNumbers.clear();
            continue;
        }
        else if (*it == ',')
        {
            it++; // Skip comma.
        }

        numbersInLine++;

        int n = 10 * number(it[0]) + number(it[1]);
        it += 1; // Move 2 forward total.

        lineNumbers.push_back(n);

#if 0
        printFmt("Searching {}\n", n);
#endif

        if (invalid)
        {
            continue;
        }

        auto ordering = m_ordering[n];

        auto finding = std::find(rules.cbegin(), rules.cend(), n);
        if (finding != rules.cend())
        {
            DEBUG_FMT("invalid {}, {} not allowed\n", lineIdx, n);

            invalid = true;
            continue;
        }

        rules.insert(rules.end(), ordering.cbegin(), ordering.cend());

#if 0
        for (auto rule : rules)
        {
            printFmt("{} ", rule);
        }
        printFmt("\n");
#endif
    }

    return sum;
}

uint64_t Day05::calculatePart2()
{
    return m_part2;
}
