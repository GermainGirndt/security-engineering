#! /bin/bash

# The script expects an argument ($1) which should be the hashed password.
input=$1

echo "Searching for password with hash $input."

# Initialize the counter to 0.
count=0

# Calculate total number of words in the dictionary.
total=$(wc -l < /usr/share/dict/words)

# Read each line (word) of the file /usr/share/dict/words.
while IFS= read -r word
do
        # Skip words that start with "-"
        if [ ${word:0:1} != "-" ]
        then
                # Extract the salt from the input (hashed password) by taking the 3rd to 11th characters of the input.
                salt=${input:3:11}

                # Hash the current word from the dictionary using the extracted salt.
                # -1 means md5
                # 2> /dev/null redirects the error output to /dev/null (the error output is not printed on the screen).
                #hash=$(openssl passwd -1 -salt $salt $word 2> /dev/null)
                hash=$(openssl passwd -1 -salt $salt $word)

                # If the newly computed hash and the input hash are same, then we found the password.
                if [ "$hash" == "$input" ]
                then
                        # Print the discovered password.
                        echo "The password is $word."
                        # Exit the script as the password has been found.
                        exit 0
                fi


                # Print the counter value in the same line. The "\r" returns the cursor to the beginning of the line.
                if (( count % 1000 == 0 )); then
                        completion=$(( (count * 100) / total ))
                        echo -ne "Words tested: $count/$total (${completion}%) \r"
                fi

                # Increment the counter.
                count=$((count+1))
        fi
done < /usr/share/dict/words

# If no match was found in the dictionary, print a message.
echo "The password has not been found."
