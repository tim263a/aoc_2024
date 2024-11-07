#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <day_index> <session_cookie>"
    exit 1
fi

year=2024
day_index="$1"
session_cookie="$2"

echo "Day index: $day_index"
echo "Session cookie: $session_cookie"

url=https://adventofcode.com/2024/day/$day_index/input
output_file=inputs/day_$day_index.txt

if [ -f $output_file ]
then
    echo "File $output_file already exists."
    exit 1
fi

mkdir -p inputs
curl $url --cookie "session=$session_cookie" --output $output_file

if [ $? -ne 0 ]
then
    echo "Failed to download input data."
    exit 1
fi

echo "Input data downloaded successfully to $output_file"
