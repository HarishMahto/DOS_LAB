#!/bin/bash

# Read two numbers from the user
echo "Enter the first number: "
read num1
echo "Enter the second number: "
read num2

# Perform arithmetic operations
echo "Addition: $((num1 + num2))"
echo "Subtraction: $((num1 - num2))"
echo "Multiplication: $((num1 * num2))"
echo "Division: $((num1 / num2))"
echo "Modulo: $((num1 % num2))"
