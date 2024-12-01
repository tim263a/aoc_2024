#!/bin/bash

(
    cd build
    cmake -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..

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

( # Run tests.
    cd build

    ctest . --output-on-failure

    if [ $? != 0 ]; then
        echo "Tests failed!"
        exit 1
    fi
)

echo ""

( # Execute binary.
    cd build

    echo "Using file $file_path as input."

    echo "$file_content" | ./aoc_main
)
