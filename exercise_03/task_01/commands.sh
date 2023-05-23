#!/bin/sh

file flash.JPG > file_data
strings file_data | grep -oba model #Offset des Kameratyps
strings file_data | grep -oba datetime #Offset der Zeit
hexdump -C file_data

gcc -o camera_data camera_data.c
echo "Calling the camera_data program with the provided image"
./camera_data file_data 

echo "Calling the camera_data program with non existent image"
./camera_data abc # Fehler, weil die Datei nicht existiert

echo "Calling the camera_data program with another image"
file test.jpg > file_data2
./camera_data file_data2 #Programm funktioniert nicht für andere Datei

strace ./camera_data file_data
#dtruss ./camera_data file_data #for Mac
