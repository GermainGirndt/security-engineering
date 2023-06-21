#! /bin/bash

# The script expects an argument ($1) which should be the hashed password.
input=$1 

# Read each line (word) of the file /usr/share/dict/words.
while IFS= read -r word
do
        # Skip words that start with "-"
        if [ ${word:0:1} != "-" ]
        then
                # Extract the salt from the input (hashed password).
                salt=${input:3:11}

                # Hash the current word from the dictionary using the extracted salt.
                hash=$(openssl passwd -1 -salt $salt $word)

                # If the newly computed hash and the input hash are same, then we found the password.
                if [ "$hash" == "$input" ]
                then
                        # Print the discovered password.
                        echo "The password is $word."
                        # Exit the script as the password has been found.
                        exit 0
                fi
        fi
done < /usr/share/dict/words

# If no match was found in the dictionary, print a message.
echo "The password has not been found."
