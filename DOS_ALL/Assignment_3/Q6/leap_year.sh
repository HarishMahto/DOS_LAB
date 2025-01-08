#!/bin/bash

# Check if the user provided a year as an argument
if [ $# -eq 0 ]; then
    # If no argument is provided, use the current year
    year=$(date +"%Y")
else
    # If an argument is provided, use it as the year
    year=$1
fi

# Check if the year is a leap year
if (( year % 4 == 0 && year % 100 != 0 )) || (( year % 400 == 0 )); then
    echo "$year is a leap year."
else
    echo "$year is not a leap year."
fi
