#!/bin/bash

# Check if three command line arguments are provided
if [ $# -ne 3 ]; then
    echo "Error: Three numbers are required."
    exit 1
fi

# Check if the command line arguments are numeric
if ! [[ $1 =~ ^[0-9]+(\.[0-9]+)?$ ]] || ! [[ $2 =~ ^[0-9]+(\.[0-9]+)?$ ]] || ! [[ $3 =~ ^[0-9]+(\.[0-9]+)?$ ]]; then
    echo "Error: All arguments must be numbers."
    exit 1
fi

# Compare the three numbers and display the smallest one
if (( $(echo "$1 < $2 && $1 < $3" | bc -l) )); then
    echo "The smallest number is $1."
elif (( $(echo "$2 < $1 && $2 < $3" | bc -l) )); then
    echo "The smallest number is $2."
else
    echo "The smallest number is $3."
fi
