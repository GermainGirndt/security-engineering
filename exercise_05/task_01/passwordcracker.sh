#! /bin/bash
input=$1
while IFS= read -r word
do
        if [ ${word:0:1} != "-" ]
        then
                salt=${input:3:11}
                hash=$(openssl passwd -1 -salt $salt $word)
                if [ "$hash" == "$input" ]
                then
                        echo "The password is $word."
                        exit 0
                fi
        fi
done < /usr/share/dict/words
echo "The password has not been found."
