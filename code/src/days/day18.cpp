#include "days/day18.h"

#include <cassert>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <queue>
#include <unordered_set>

#include "util/print_fmt.h"
#include "util/read_input.h"

Day18::Day18()
    : m_buffer(32000)
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

void Day18::parseInput()
{
    read_stdio_into_buffer(m_buffer);

    for (auto it = m_buffer.cbegin(); *it != '\0'; it++)
    {
        int64_t x = readNumber(it);
        it++; // ","
        int64_t y = readNumber(it);
        // it++; // "\n"

        m_coordinates.emplace_back(x, y);
    }

    printFmt("{} coordinates\n", m_coordinates.size());
}

#if 1 // real data
constexpr std::size_t WIDTH = 71;
constexpr std::size_t HEIGHT = 71;
constexpr std::size_t FALLS = 1024;
#else // example
constexpr std::size_t WIDTH = 7;
constexpr std::size_t HEIGHT = 7;
constexpr std::size_t FALLS = 12;
#endif

uint64_t Day18::calculatePart1()
{
    uint64_t sum = 0;

    struct Node
    {
        bool corrupted = false;
        bool path = false;

        Node* cameFrom = nullptr;
        int64_t gScore = INT64_MAX;
        int64_t fScore = INT64_MAX;
    };

    struct NodePtrCmp
    {
        bool operator()(const Node* n0, const Node* n1) {
            return n0->fScore > n1->fScore;
        }
    };

    std::vector<Node> map(WIDTH * HEIGHT);

    assert(m_coordinates.size() <= FALLS);

    for (std::size_t i = 0; i < FALLS; i++)
    {
        Coordinate pos = m_coordinates[i];
        DEBUG_FMT("{} {} --> {}/{}\n",
            pos.x, pos.y, pos.y * WIDTH + pos.x, map.size());
        map[pos.y * WIDTH + pos.x].corrupted = true;
    }

    for (std::size_t y = 0; y < HEIGHT; y++)
    {
        for (std::size_t x = 0; x < WIDTH; x++)
        {
            Node& node = map[y * WIDTH + x];
            printFmt("{:c}", node.corrupted ? 'X' : '.');
        }
        printFmt("\n");
    }

    auto nodeAt = [&] (std::size_t x, std::size_t y)
    {
        return map.data() + (y * WIDTH + x);
    };

    // A* algorithm.
    std::unordered_set<Node*> isInOpen;
    std::priority_queue<Node*, std::vector<Node*>, NodePtrCmp> open;
    open.push(map.data());
    isInOpen.insert(map.data());

    map[0].gScore = 0;
    map[0].fScore = 0;

    while (!open.empty())
    {
        Node* current = open.top();
        open.pop();
        isInOpen.erase(map.data());

        if (current == &*map.rbegin())
        {
            printFmt("Found path\n");

            Node* pathNode = current;
            while (pathNode)
            {
                sum += 1;

                pathNode->path = true;
                pathNode = pathNode->cameFrom;
            }

            break;
        }

        std::size_t offset = current - map.data();
        std::size_t x = offset % WIDTH;
        std::size_t y = offset / WIDTH;

        std::vector<Node*> neighbors;

        if (x > 0)
        {
            neighbors.push_back(nodeAt(x - 1, y));
        }
        if (x < WIDTH - 1)
        {
            neighbors.push_back(nodeAt(x + 1, y));
        }

        if (y > 0)
        {
            neighbors.push_back(nodeAt(x, y - 1));
        }
        if (y < HEIGHT - 1)
        {
            neighbors.push_back(nodeAt(x, y + 1));
        }

        int64_t tentativeScore = current->gScore + 1;
        for (Node* neighbor : neighbors)
        {
            if (neighbor->corrupted)
            {
                continue;
            }

            std::size_t nX = (neighbor - map.data()) % WIDTH;
            std::size_t nY = (neighbor - map.data()) / WIDTH;

            if (neighbor->gScore > tentativeScore)
            {
                DEBUG_FMT("Evaluating neighbor {}|{} ... ", nX, nY);
                neighbor->cameFrom = current;
                neighbor->gScore = tentativeScore;
                neighbor->fScore = tentativeScore + (WIDTH - x) + (HEIGHT - y);
                if (!isInOpen.contains(neighbor))
                {
                    DEBUG_FMT("adding\n");

                    open.push(neighbor);
                    isInOpen.insert(neighbor);
                }
                else
                {
                    DEBUG_FMT("skipping\n");
                }
            }
        }
    }

    for (std::size_t y = 0; y < HEIGHT; y++)
    {
        for (std::size_t x = 0; x < WIDTH; x++)
        {
            Node& node = map[y * WIDTH + x];
            uint8_t symbol = '.';
            if (node.corrupted)
            {
                if (node.path)
                {
                    symbol = '@';
                }
                else
                {
                    symbol = '#';
                }
            }
            else if (node.path)
            {
                symbol = 'O';
            }
            printFmt("{:c}", symbol);
        }
        printFmt("\n");
    }

    return sum - 1;
}

uint64_t Day18::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
