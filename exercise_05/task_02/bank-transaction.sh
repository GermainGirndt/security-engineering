#!/bin/bash
# Ignore the interrupt signal (Ctrl+C)
trap '' SIGINT

# Start an infinite loop
while true; do
    # Ask for the username and TAN
    read -p "Enter username: " username
    read -p "Enter TAN: " tan

    # Define the file path
    file="TAN/${username}.txt"

    # If the TAN file for the user does not exist, deny access
    if [ ! -f $file ]; then
        echo "Access denied (unknown user or exhausted TAN list)"
        continue
    fi

    # Read the first line from the TAN file
    first_line=$(head -n 1 $file)
    sha_256_hashed_tan=$( echo "$tan" | openssl dgst -sha256 )

    # If the entered TAN matches the first line, grant access and delete the used TAN
    if [ "$sha_256_hashed_tan" == "$first_line" ]; then
        # 'sed -i '1d' $file' deletes the first line from the file
        sed -i '' '1d' $file # -i = in place; 1d = first line
        echo "Access granted"
    else
        # If the TAN does not match, deny access
        echo "Access denied (incorrect TAN)"
    fi
done
