#!/bin/bash

# Prompt the user to enter internal marks and attendance percentage
echo "Enter internal marks (out of 50): "
read internal_marks

echo "Enter attendance percentage: "
read attendance_percentage

# Check if the internal marks and attendance percentage are eligible
if (( internal_marks >= 20 && attendance_percentage >= 75 )); then
    echo "Allowed for Semester"
else
    echo "Not allowed"
fi
