#!/bin/bash

# Prompt the user to enter a character
echo "Enter a character: "
read input

# Check if the user entered more than one character
if [ ${#input} -gt 1 ]; then
    echo "You have entered more than one character."
    exit 0
fi

# Check if the character is a lower case alphabet
if [[ $input =~ [a-z] ]]; then
    echo "You entered a lower case alphabet."
    exit 0
fi

# Check if the character is an upper case alphabet
if [[ $input =~ [A-Z] ]]; then
    echo "You entered an upper case alphabet."
    exit 0
fi

# Check if the character is a digit
if [[ $input =~ [0-9] ]]; then
    echo "You have entered a digit."
    exit 0
fi

# If none of the above conditions are true, the character is a special symbol
echo "You have entered a special symbol."
