#!/bin/sh


# Store command-line arguments in an array
args=("$@")

# Check if any arguments were provided
if [ ${#args[@]} -eq 0 ]; then
    echo "No arguments provided."
    exit 1
fi

# Loop through the array and print each argument
for arg in "${args[@]}"; do
    echo "Hello $arg"
done

exit 0