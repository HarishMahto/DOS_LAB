#!/bin/bash

# Prompt the user to enter the cost price and selling price
echo "Enter the cost price: "
read cost_price
echo "Enter the selling price: "
read selling_price

# Check if the input values are numeric
if ! [[ $cost_price =~ ^[0-9]+(\.[0-9]+)?$ ]] || ! [[ $selling_price =~ ^[0-9]+(\.[0-9]+)?$ ]]; then
    echo "Invalid input. Please enter numeric values."
    exit 1
fi

# Calculate the profit or loss
if (( $(echo "$selling_price > $cost_price" | bc -l) )); then
    profit=$(echo "$selling_price - $cost_price" | bc -l)
    echo "The seller has made a profit of $profit."
elif (( $(echo "$selling_price < $cost_price" | bc -l) )); then
    loss=$(echo "$cost_price - $selling_price" | bc -l)
    echo "The seller has incurred a loss of $loss."
else
    echo "The seller has neither made a profit nor incurred a loss."
fi
