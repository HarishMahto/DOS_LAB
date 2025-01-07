#!/bin/bash

# Check if two file names are provided as command line arguments
if [ $# -ne 2 ]; then
    echo "Error: Two file names are required."
    exit 1
fi

# Check if the files exist
if [ ! -f "$1" ] || [ ! -f "$2" ]; then
    echo "Error: One or both files do not exist."
    exit 1
fi

# Compare the contents of the two files
if cmp --silent "$1" "$2"; then
    # If the files are the same, delete the second file
    rm "$2"
    echo "Files $1 and $2 have same content."
    echo "So $2 is deleted."
else
    # If the files are different, display a message
    echo "Files $1 and $2 have different content."
fi
