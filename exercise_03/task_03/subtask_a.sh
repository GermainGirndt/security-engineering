#!/bin/sh


# Store command-line arguments in an array
args=("$@")

# Loop through the array and print each argument
for arg in "${args[@]}"; do
    echo "Hello $arg"
done

exit 0