#!/bin/bash

(
    cd build
    cmake ..

    cmake --build .
)

(
    cd build

    ./aoc_wannabe
)
