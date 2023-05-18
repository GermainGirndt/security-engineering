#!/bin/bash

# Check the input parameters
if [ $# -ne 1 ]; then
  echo "Invalid input. This script should receive exactly one argument."
  exit 1
fi

# Check if ffmpeg is installed
if ! command -v ffmpeg &> /dev/null; then
  echo "Error: ffmpeg is not installed."
  exit 1
fi

input_file="$1"

# % is a parameter expansion; it removes the .wav after the delimitator %
output_file="${input_file%.wav}.mp3"  # Generate output file name by replacing .wav extension with .mp3

# Convert WAV to MP3 using ffmpeg
ffmpeg -i "$input_file" "$output_file"

# Check the exit status of ffmpeg
if [ $? -eq 0 ]; then
  echo "Conversion successful. Output file: $output_file"
else
  echo "Conversion failed."
  exit 1
fi

