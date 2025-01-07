#!/bin/bash

# Prompt the user to enter a day
echo "Enter a day (Monday to Sunday): "
read day

# Define the class schedules for each day
declare -A class_schedules
class_schedules[Monday]="9:00 AM - 10:00 AM, Room 101"
class_schedules[Tuesday]="10:00 AM - 11:00 AM, Room 102"
class_schedules[Wednesday]="11:00 AM - 12:00 PM, Room 103"
class_schedules[Thursday]="12:00 PM - 1:00 PM, Room 104"
class_schedules[Friday]="1:00 PM - 2:00 PM, Room 105"
class_schedules[Saturday]="No class on Saturday"
class_schedules[Sunday]="Holiday"

# Check if the day is valid
if [[ ${class_schedules[$day]} ]]; then
    # Display the class schedule for the day
    echo "DOS class time on $day: ${class_schedules[$day]}"
else
    # Display an error message if the day is not valid
    echo "Invalid day. Please enter a day between Monday and Sunday."
fi
