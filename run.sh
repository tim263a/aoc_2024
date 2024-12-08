#!/bin/bash

day_idx=-1

if [ $# -gt 0 ]
then
    day_idx=$1
fi

(
    cd build

    cmake -GNinja \
        -DCMAKE_BUILD_TYPE=Release \
        -DDAY_IDX=$day_idx \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
        ../code

    cmake --build .
)

if [ $? != 0 ]; then
    echo "Build failed!"
    exit 1
fi

build_only=0

file_path=inputs/day_$1.txt
if [ $# -lt 1 ]; then
    echo "Usage: $0 <day_index> [<input_file>]"
    build_only=1
elif [ $# -lt 2 ]; then
    file_path=inputs/day_$1.txt
elif [ $# -ge 2 ]; then
    file_path=$2
fi

if [ $build_only -eq 0 ] && [ -f $file_path ]; then
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

if [ $build_only -ne 0 ]
then
    echo "Running in build only mode."
    echo "See usage above for how to execute for a certain day."
    exit 1
fi

echo ""

( # Execute binary.
    cd build

    echo "Using file $file_path as input."

    echo "$file_content" > hyperfine_input.txt
    rm hyperfile_output.txt

    hyperfine --input ./hyperfine_input.txt --output ./hyperfine_output.txt "./aoc_main "$@""

    tail hyperfine_output.txt
)
