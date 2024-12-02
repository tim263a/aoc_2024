#include "days/day02.h"

#include <cstdint>
#include <cmath>
#include <sstream>
#include <vector>

#include "util/print_fmt.h"
#include "util/read_input.h"

void Day02::parseInput()
{
    m_lines = read_stdin_lines();
}

static int8_t signum(int8_t v)
{
    return v == 0 ? 0 : (std::signbit(v) ? -1 : 1);
}

uint64_t Day02::calculatePart1()
{
    debugFmt("Read {:d} lines\n", m_lines.size());

    uint64_t sum = 0;

    for (std::string& line : m_lines)
    {
        std::stringstream ss(line);

        std::optional<int8_t> lineSignum;
        int32_t prev = 0;
        int32_t now = 0;

        bool fail = false;

        ss >> prev;

        while (ss >> now)
        {
            int32_t diff = now - prev;
            uint32_t abs = std::abs(diff);
            debugFmt("({:d} {:d})", now, diff);
            if (!lineSignum)
            {
                lineSignum = signum(diff);
            }
            else if (*lineSignum != signum(diff))
            {
                fail = true;
            }

            if (abs < 1 || abs > 3)
            {
                fail = true;
            }

            prev = now;
        }

        debugFmt(" --> {}\n", !fail);

        if (!fail)
        {
            sum += 1;
        }
    }

    return sum;
}

uint64_t Day02::calculatePart2()
{
    debugFmt("Read {:d} lines\n", m_lines.size());

    uint64_t sum = 0;

    for (std::string& line : m_lines)
    {
        std::stringstream ss(line);

        std::optional<int8_t> lineSignum;
        int32_t prev = 0;
        int32_t now = 0;

        uint32_t counter = 1;
        uint32_t sgnFails = 0;
        uint32_t absFails = 0;

        ss >> prev;

        while (ss >> now)
        {
            counter++;
            int32_t diff = now - prev;
            uint32_t abs = std::abs(diff);
            debugFmt("({:d} {:d})", now, diff);
            if (!lineSignum)
            {
                lineSignum = signum(diff);
            }
            else if (*lineSignum != signum(diff))
            {
                sgnFails++;
            }

            if (abs < 1 || abs > 3)
            {
                absFails++;
            }

            prev = now;
        }

        debugFmt(" --> {} {} {}\n", sgnFails, counter, absFails);

        if ((sgnFails + absFails <= 1) || ((counter - sgnFails) + absFails) <= 1)
        {
            sum += 1;
        }
    }

    return sum;
}
