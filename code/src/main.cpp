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
#include "days/day03.h"
#include "days/day04.h"
#include "days/day05.h"
#include "days/day06.h"
#include "days/day07.h"
#include "days/day08.h"
#include "days/day09.h"
#include "days/day11.h"
#include "days/day12.h"
#include "days/day13.h"
#include "days/day14.h"
#include "days/day15.h"
#include "days/day16.h"
#include "days/day17.h"
#include "days/day18.h"
#include "days/day19.h"
#include "days/day21.h"

bool g_verbose = false;

int main(int argc, char** argv)
{
#ifndef NDEBUG
    auto start = std::chrono::high_resolution_clock::now();
#endif

#ifndef NDEBUG
    uint32_t dayIdx = argc >= 2 ? std::stoi(argv[1]) : DAY_IDX;
    g_verbose = argc >= 3 && (argv[2] == std::string("1"));
#else
    const int_fast32_t dayIdx = DAY_IDX;
#endif

    DEBUG_FMT("Running for day {:d}, ", dayIdx);
    DEBUG_FMT("debug {:s}\n", g_verbose ? "enabled" : "disabled");

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
        case 3:
            day = std::make_unique<Day03>();
            break;
        case 4:
            day = std::make_unique<Day04>();
            break;
        case 5:
            day = std::make_unique<Day05>();
            break;
        case 6:
            day = std::make_unique<Day06>();
            break;
        case 7:
            day = std::make_unique<Day07>();
            break;
        case 8:
            day = std::make_unique<Day08>();
            break;
        case 9:
            day = std::make_unique<Day09>();
            break;
        case 11:
            day = std::make_unique<Day11>();
            break;
        case 12:
            day = std::make_unique<Day12>();
            break;
        case 13:
            day = std::make_unique<Day13>();
            break;
        case 14:
            day = std::make_unique<Day14>();
            break;
        case 15:
            day = std::make_unique<Day15>();
            break;
        case 16:
            day = std::make_unique<Day16>();
            break;
        case 17:
            day = std::make_unique<Day17>();
            break;
        case 18:
            day = std::make_unique<Day18>();
            break;
        case 19:
            day = std::make_unique<Day19>();
            break;
        case 21:
            day = std::make_unique<Day21>();
            break;
    }

    day->parseInput();

    uint64_t part1 = day->calculatePart1();
    uint64_t part2 = day->calculatePart2();

    // printFmt("{:d} {:d}\n", part1, part2);

    printf("%lu %lu\n", part1, part2);

#ifndef NDEBUG
    auto end = std::chrono::high_resolution_clock::now();
    printFmt("{}", end - start);
#endif

    return 0;
}
