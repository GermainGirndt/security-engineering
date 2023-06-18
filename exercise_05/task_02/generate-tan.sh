#!/bin/bash
# Fetch the username and count from command line arguments
username=$1
count=$2

# If either the username or count is not provided, print usage and exit
if [ -z "$username" ] || [ -z "$count" ]; then
    echo "Usage: $0 <username> <count>"
    exit 1
fi

# Create the TAN directory if it doesn't exist
mkdir -p TAN

# Generate 'count' number of random 6 digit numbers and append them to the user's TAN file
for (( i=0; i<$count; i++ )); do
    number=$(od -An -N4 -i /dev/urandom | sed 's/[^0-9]*//g') # -An = not output address offsets; -N4 = 4 bytes; -i = decimal format 
    rand=$(printf "%06d" $(( number % 1000000 )))
    echo $rand >> "TAN/${username}.txt"
done

# Print out a success message
echo "Generated $count TANs for $username"
