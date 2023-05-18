#!/bin/bash

# Check if program name is provided
if [ $# -ne 1 ]; then
  echo "Invalid input. This script should receive exactly one argument."
  exit 1
fi

program="$1"

# Split the PATH variable by ':' delimiter
# IFS  determines how Bash splits input into separate fields, which is particularly useful in operations involving word splitting and input parsing.
# Should just be used locally
# () indicate that the value is to be treated as an array.
IFS=':' directories=($PATH)

# Iterate over each directory in the PATH
for directory in "${directories[@]}"; do
  # Check if the program exists and is executable in the current directory
  if [ -x "${directory}/${program}" ]; then
    echo "${directory}/${program}"
    exit 0
    break
  fi
done



echo "Program '$program' not found in PATH directories."
exit 1
