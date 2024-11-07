#!/bin/bash

(
    cd build
    cmake ..

    cmake --build .
)

file_path=inputs/day_$1.txt
if [ $# -lt 1 ]; then
    echo "Usage: $0 <day_index>"
    exit 1
elif [ -f $file_path ]; then
    file_content=$(cat $file_path)
else
    echo "File $file_path not found."
    exit 1
fi

(
    cd build

    echo $file_content | ./aoc_wannabe
)
