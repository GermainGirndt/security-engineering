#!/bin/bash

# Function to call the appropriate viewer program
open_file() {
  local file="$1"
  local file_type=$(file -b "$file")

  case "$file_type" in
    *image*)
      /usr/local/bin/xv "$file"  # Call the xv program for image files
      ;;
    *PDF*)
      xpdf "$file"  # Call the xpdf program for PDF files
      ;;
    *text*)
      less "$file"  # Call the less program for text files
      ;;
    *OpenDocument*)
      libreoffice "$file"  # Call the libreoffice program for OpenDocument text files
      ;;
    *)
       xdg-open $file
       if [ $? -ne 0 ]; then
          echo "Format not supported"
          exit 1
       fi

  esac
}

# Check the input parameters
if [ $# -ne 1 ]; then
  echo "Invalid input. This script should receive exactly one argument."
  exit 1
fi


# Pass the file to the open_file function
if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Running on macOS"
    open "$1"
elif [[ "$OSTYPE" == "linux-gnu" ]]; then
    echo "Running on Linux"
    open_file "$1"
else
    echo "Unsupported operating system"
    exit 1
fi

exit 0