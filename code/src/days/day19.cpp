#include "days/day19.h"

#include <algorithm>
#include <cstddef>
#include <memory>
#include <string>

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

static uint8_t charIndex(uint8_t c)
{
    switch (c)
    {
        case 'w':
            return 0;
        case 'u':
            return 1;
        case 'b':
            return 2;
        case 'r':
            return 3;
        case 'g':
            return 4;
        default:
            printFmt("Invalid char: {:c}\n", c);
            std::exit(1);
    };
}

static char charFromIndex(uint8_t c)
{
    switch (c)
    {
        case 0:
            return 'w';
        case 1:
            return 'u';
        case 2:
            return 'b';
        case 3:
            return 'r';
        case 4:
            return 'g';
        default:
            printFmt("Invalid char: {:c}\n", c);
            std::exit(1);
    };
}

void Day19::printTree(const Node& node, std::size_t idx, uint8_t indent,
    const std::string& prefix)
{
    if (node.isValid)
    {
        printFmt("{:{}s}{:s}\n", "", indent * 2, prefix);
    }

    for (std::size_t i = 0; i < node.subNodes.size(); i++)
    {
        if (node.subNodes[i])
        {
            printTree(*node.subNodes[i], i, indent + 1, prefix + charFromIndex(i));
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

    Node root;

    for (const std::string& component : m_components)
    {
        Node* node = &root;

        for (std::size_t i = 0; i < component.size(); i++)
        {
            std::size_t cIdx = charIndex(component[i]);
            std::unique_ptr<Node>& subNode = node->subNodes[cIdx];

            if (!subNode)
            {
                subNode = std::make_unique<Node>();
            }

            node = subNode.get();
        }

        node->isValid = true;
    }

    printTree(root, 0, 0);

    return sum;
}

uint64_t Day19::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
