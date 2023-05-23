#!/bin/bash

# Function to call the appropriate viewer program
open_file() {
  local file="$1"
  local file_type=$(file -b "$file")

  case "$file_type" in
    *image*)
      #/usr/local/bin/xv "$file"  # Call the xv program for image files
      open -a Preview "$file" 
      ;;
    *PDF*)
      #xpdf "$file"  # Call the xpdf program for PDF files
      open -a Preview "$file" 
      ;;
    *text*)
      less "$file"  # Call the less program for text files
      ;;
    *OpenDocument*)
      #libreoffice "$file"  # Call the libreoffice program for OpenDocument text files
      open -a TextEdit  "$file"
      ;;
    *)
        echo "Format not supported"
        exit 1

  esac
}

# Check the input parameters
if [ $# -ne 1 ]; then
  echo "Invalid input. This script should receive exactly one argument."
  exit 1
fi


open_file "$1"

exit 0