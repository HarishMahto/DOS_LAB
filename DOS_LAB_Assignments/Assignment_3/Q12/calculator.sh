#!/bin/bash

# Check if three command line arguments are provided
if [ $# -ne 3 ]; then
    echo "Invalid input"
    echo "Enter input in following format: op1 operator op2"
    exit 1
fi

# Check if the second argument is a valid operator
valid_operators="+ - x / % ^"
if [[ $valid_operators != *"$2"* ]]; then
    echo "Invalid input"
    echo "Enter input in following format: op1 operator op2"
    exit 1
fi

# Perform the arithmetic operation
case $2 in
    "+")
        result=$(echo "scale=2; $1 + $3" | bc)
        ;;
    "-")
        result=$(echo "scale=2; $1 - $3" | bc)
        ;;
    "x")
        result=$(echo "scale=2; $1 * $3" | bc)
        ;;
    "/")
        if [ $3 -eq 0 ]; then
            echo "Error: Division by zero"
            exit 1
        fi
        result=$(echo "scale=2; $1 / $3" | bc)
        ;;
    "%")
        if [ $3 -eq 0 ]; then
            echo "Error: Division by zero"
            exit 1
        fi
        result=$(echo "$1 % $3" | bc)
        ;;
    "^")
        result=$(echo "scale=2; $1 ^ $3" | bc)
        ;;
esac

# Display the result
echo "$1 $2 $3 = $result"
