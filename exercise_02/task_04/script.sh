#!/bin/bash


# Constants
WISHED_NUMBER_OF_BITS=128
NUMBER_OF_BITS_PER_HEXADECIMAL_VALUE=4
HEXADECIMAL_NUMBERS_NEEDED=$((WISHED_NUMBER_OF_BITS / NUMBER_OF_BITS_PER_HEXADECIMAL_VALUE))

CUT_START=9
OFFSET_EOL_AND_EMPTY_STRING=-2
CUT_END=$((CUT_START + HEXADECIMAL_NUMBERS_NEEDED - OFFSET_EOL_AND_EMPTY_STRING))

echo "Hexadecimal numbers needed:"
echo $HEXADECIMAL_NUMBERS_NEEDED
echo "Cut start:"
echo $CUT_START
echo "Cut end with offset:"
echo $CUT_END
echo "------------------"

# Original Command Output
echo "Original Command Output:"
original_command=$(od -t x4 /dev/urandom | head -1)
echo $original_command
echo "Length:"
len_original_command=$(echo $original_command | wc -c)
echo $len_original_command
echo

# Command without spaces
echo "Command without spaces:"
command_without_spaces=$(echo $original_command | sed -e "s/ //g")
echo $command_without_spaces
echo "Length:"
len_command_without_spaces=$(echo $command_without_spaces | wc -c)
echo $len_command_without_spaces
echo

# Number of spaces
echo "Number of spaces:"
number_spaces=$((len_original_command - len_command_without_spaces))
echo $number_spaces
echo "------------------"
echo

# Cutting
echo "Cutted string:"
cut_string=$(echo $original_command | cut -c "$CUT_START-$CUT_END" | sed -e "s/ //g")
echo $cut_string
len_cut_string=$(echo $cut_string | wc -c)
echo "Length: "
echo $len_cut_string
echo "------------------"

# Better alternative (but not asked by the task): Exchanging sed and cut (Needs to alter the offset to 1)
# echo "Cutting..."
# cut_string=$(echo $original_command | sed -e "s/ //g" | cut -c "$CUT_START-$CUT_END")
# echo $cut_string
# len_cut_string=$(echo $cut_string | wc -c)
# echo $len_cut_string

echo
echo "Creating the hash as Alice did for the key: $cut_string"
openssl dgst -sha256 -mac HMAC -macopt "hexkey:$cut_string" /etc/services
echo
