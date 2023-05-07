
# Compiler
CC = gcc

# Compiler flags
# -Wall all warning messages enabled
# -Wextra additional warning messages enabled
CFLAGS = -Wall -Wextra

# Target executable name; depends on the print_file_info.o rule
TARGET = print_file_info

# Default target: build the executable
all: $(TARGET)

# Rule to build the executable using the necessary libraries
$(TARGET): print_file_info.o
	$(CC) $(CFLAGS) print_file_info.o -o $(TARGET)

# Rule to compile the source file into an object file
print_file_info.o: print_file_info.c
	$(CC) $(CFLAGS) -c print_file_info.c

# Rule to clean the build artifacts
clean:
	rm -f $(TARGET) *.o
