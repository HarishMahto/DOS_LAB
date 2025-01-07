#!/bin/bash

# Prompt the user to enter a five-digit number
echo "Enter a five-digit number: "
read num

# Check if the number is a five-digit number
if [ ${#num} -ne 5 ] || ! [[ $num =~ ^[0-9]+$ ]]; then
    echo "Invalid input. Please enter a five-digit number."
    exit 1
fi

# Calculate the sum of the digits
sum=0
for ((i=0; i<${#num}; i++)); do
    digit=${num:$i:1}
    sum=$((sum + digit))
done

# Print the sum of the digits
echo "The sum of the digits is: $sum"
