#!/bin/bash

while read line
do
    characters=${#line}
    words=$(echo "$line" | wc -w)

    echo "Line: $line"
    echo "Characters: $characters"
    echo "Words: $words"
done < input.txt
