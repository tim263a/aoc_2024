#include "days/day06.h"

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <unordered_map>
#include <utility>
#include <vector>

#include "util/print_fmt.h"
#include "util/read_input.h"

Day06::Day06()
{

}

void Day06::parseInput()
{
    read_stdio_into_buffer(m_buffer);
}

int findWall(std::vector<int> walls, int startPos, int direction)
{
    DEBUG_FMT("startPos {} direction {} Known Walls: ", startPos, direction);
    for (auto wall : walls)
    {
        DEBUG_FMT("{} ", wall);
    }
    DEBUG_FMT("\n");

    auto pos = std::find_if(walls.cbegin(), walls.cend(), [startPos] (int value) {
        return value >= startPos;
    });

    if (pos == walls.cend())
    {
        if (direction == -1)
        {
            return *walls.crbegin();
        }

        // Running outside area.
        return -1;
    }

    return pos[direction == -1 ? -1 : 0];
}

uint64_t Day06::calculatePart1()
{
    std::size_t width = 0;
    for (auto it = m_buffer.cbegin(); *it != '\n'; it++, width++) { }
    std::size_t height = m_buffer.size() / (width + 1);

    // Assume that start position is not in first line, because it would make for
    // a really boring puzzle (and would be highly unfair).

    printFmt("Width {} Height {}\n", width, height);

    std::size_t posX = 0;
    std::size_t posY = 0;
    std::size_t startX = 0;
    std::size_t startY = 0;

    for (auto it = m_buffer.cbegin(); it != m_buffer.cend(); it++, posX++)
    {
        if (*it == '\n')
        {
            posY += 1;
            posX = -1;
        }
        else if (*it == '^')
        {
            startX = posX;
            startY = posY;
        }
        else if (*it == '#')
        {
            printFmt("Wall at X {} Y {}\n", posX, posY);

            m_wallsX[posX].push_back(posY);
            m_wallsY[posY].push_back(posX);
        }
    }

    printFmt("Start X {} Y {}\n", startX, startY);

    std::size_t directionIdx = 0;
    std::vector<int> directions = { -1, 1, 1, -1 };
    decltype(m_wallsX)* wallsFaced = &m_wallsX;
    decltype(m_wallsX)* wallsNotFaced = &m_wallsY;
    decltype(m_segmentsX)* segmentsFaced = &m_segmentsY;
    decltype(m_segmentsY)* segmentsNotFaced = &m_segmentsX;

    int orthogonalPos = startX;
    int sightlinePos = startY;
    int direction = -1;

    int testSteps = 0;
    int jumpLength = 0;

    while (testSteps++ < 1000000)
    {
        int direction = directions[directionIdx];
        directionIdx = (directionIdx + 1) % directions.size();

        printFmt("orthoPos {} sightlinePos {}\n", orthogonalPos, sightlinePos);

        int posWall = findWall((*wallsFaced)[orthogonalPos], sightlinePos, direction);
        if (posWall == -1)
        {
            break;
        }

        jumpLength += std::abs(sightlinePos - posWall);

        int s1 = sightlinePos;
        int s2 = posWall - 2 * direction;
        segmentsFaced->push_back({
            .orthoPos = orthogonalPos,
            .start = std::min(s1, s2),
            .end = std::max(s1, s2)
        });

        sightlinePos = posWall - direction;
        printFmt("Found Wall at {} posBeforeWall {} directionIdx {}\n",
            posWall, sightlinePos, (directionIdx + 3) % 4);

        const int maxDirectionLength = std::max(width, height);
        int visitHash = directionIdx * maxDirectionLength * maxDirectionLength + maxDirectionLength * posWall + orthogonalPos;
        if (m_visited.contains(visitHash))
        {
            break;
        }
        else
        {
            m_visited.insert(visitHash);
        }

        std::swap(wallsFaced, wallsNotFaced);
        std::swap(segmentsFaced, segmentsNotFaced);
        std::swap(sightlinePos, orthogonalPos);
    }

    printFmt("Jumped {} times, jumpLength {}\n", testSteps, jumpLength);

    printFmt("Segments x {} y {}:\n", m_segmentsX.size(), m_segmentsY.size());
    for (auto segment : m_segmentsX)
    {
        printFmt("X ortho {} start {} end {} length {}\n",
            segment.orthoPos, segment.start, segment.end, segment.end - segment.start);
    }
    for (auto segment : m_segmentsY)
    {
        printFmt("Y ortho {} start {} end {} length {}\n",
            segment.orthoPos, segment.start, segment.end, segment.end - segment.start);
    }

    std::sort(m_segmentsX.begin(), m_segmentsX.end(),
        [] (const Segment& s1, const Segment& s2) {
            return s1.start < s2.start;
        });

    std::sort(m_segmentsY.begin(), m_segmentsY.end(),
        [] (const Segment& s1, const Segment& s2) {
            return s1.orthoPos < s2.orthoPos;
        });

    int intersections = 1;

    auto itYSearchStart = m_segmentsY.cbegin();
    for (const auto& sX : m_segmentsX)
    {
        int orthoPos = sX.orthoPos;
        int start = sX.start;
        int end = sX.end;

        while (itYSearchStart != m_segmentsY.cend() &&
            itYSearchStart->orthoPos < start) { }

        auto itYSearch = itYSearchStart;

        for (auto itY = itYSearchStart; itY != m_segmentsY.cend() && itY->orthoPos < end; itY++)
        {
            if (itY->start > orthoPos || itY->end < orthoPos)
            {
                continue;
            }

            intersections += 1;

            printFmt("Intersection candidate: xO {} xS {} xE {} yO {} yS {} yE {}\n",
                sX.orthoPos, sX.start, sX.end,
                itY->orthoPos, itY->start, itY->end);
        }
    }

    return jumpLength - intersections;
}

uint64_t Day06::calculatePart2()
{
    uint64_t sum = 0;

    return sum;
}
