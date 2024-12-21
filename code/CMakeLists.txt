cmake_minimum_required(VERSION 3.28)

project(aoc_wannabe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -fdata-sections -ffunction-sections")

remove_definitions(-DNDEBUG) # Don't know why it's set in Release build ...

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/Catch2
    ${CMAKE_CURRENT_BINARY_DIR}/lib/Catch2)

# Common code base target (INTERFACE library)
add_library(common INTERFACE)
target_sources(common
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/util/read_input.cpp
)
target_include_directories(common
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/api
)
if (${DAY_IDX})
    target_compile_definitions(common
        INTERFACE -DDAY_IDX=${DAY_IDX}
    )
endif()

# Main method target
add_executable(aoc_main)
target_sources(aoc_main
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day01.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day02.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day03.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day04.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day05.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day06.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day07.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day08.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day09.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day11.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day12.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day13.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day14.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day15.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day16.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day17.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day18.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day19.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/days/day21.cpp
)
target_link_libraries(aoc_main
    common
)
target_compile_options(aoc_main
    PUBLIC "-Wall"
)
target_link_options(aoc_main
    PUBLIC "-Wl,--gc-sections"
    PUBLIC "-static"
)

# Test main target for catch_discover_tests
add_executable(aoc_test)
target_sources(aoc_test
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test/main.test.cpp
)
target_link_libraries(aoc_test
    common
    Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(aoc_test)
