#include <chrono>
#include <cstdint>
#include <cstdio>

#include <iostream>
#include <memory>
#include <string>

#include "util/print_fmt.h"

#include "days/day.h"
#include "days/day01.h"
#include "days/day02.h"

bool g_verbose = false;

int main(int argc, char** argv)
{
    auto start = std::chrono::high_resolution_clock::now();

    uint32_t dayIdx = argc >= 2 ? std::stoi(argv[1]) : DAY_IDX;
    g_verbose = argc >= 3 && (argv[2] == std::string("1"));

    debugFmt("Running for day {:d}, ", dayIdx);
    debugFmt("debug {:s}\n", g_verbose ? "enabled" : "disabled");

    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::unique_ptr<Day> day;
    switch (dayIdx)
    {
        default:
        case 1:
            day = std::make_unique<Day01>();
            break;
        case 2:
            day = std::make_unique<Day02>();
            break;
    }

    day->parseInput();

    uint64_t part1 = day->calculatePart1();
    uint64_t part2 = day->calculatePart2();

    printFmt("{:d} {:d}\n", part1, part2);

    auto end = std::chrono::high_resolution_clock::now();
    printFmt("{}", end - start);

    return 0;
}
