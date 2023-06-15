#! /bin/bash
while IFS= read -r word
do
        if [ ${word:0:1} != "-" ]
        then
                hash=$(openssl passwd -1 -salt ZYXWVUTS $word)
                if [ "$hash" == "$1" ]
                then
                        echo "The password is $word."
                        exit 0
                fi
        fi
done < /usr/share/dict/words
echo "The password has not been found."
