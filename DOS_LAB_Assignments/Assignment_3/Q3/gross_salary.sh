#!/bin/bash

# Read basic salary from the user
echo "Enter Ramesh's basic salary: "
read basic_salary

# Calculate dearness allowance and house rent allowance
dearness_allowance=$(bc -l <<< "$basic_salary * 0.4")
house_rent_allowance=$(bc -l <<< "$basic_salary * 0.2")

# Calculate gross salary
gross_salary=$(bc -l <<< "$basic_salary + $dearness_allowance + $house_rent_allowance")

# Display gross salary
echo "Ramesh's gross salary is: $gross_salary"
