#!/bin/sh

file flash.JPG > file_data
strings file_data | grep -oba model #Offset des Kameratyps
strings file_data | grep -oba datetime #Offset der Zeit
hexdump -C file_data

gcc -o camera_data camera_data.c
camera_data file_data

camera_data abc #Fehler, weil Datei nicht existiert

file test.jpg > file_data2
camera_data file_data2 #Programm funktioniert nicht für andere Datei

strace camera_data file_data
