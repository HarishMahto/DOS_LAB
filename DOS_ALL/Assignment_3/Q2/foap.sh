#!/bin/bash

# Read two numbers from the user
echo "Enter the first number: "
read num1
echo "Enter the second number: "
read num2

# Perform arithmetic operations
echo "Addition: $(bc -l <<< "$num1 + $num2")"
echo "Subtraction: $(bc -l <<< "$num1 - $num2")"
echo "Multiplication: $(bc -l <<< "$num1 * $num2")"
echo "Division: $(bc -l <<< "$num1 / $num2")"
