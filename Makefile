# Makefile for Bookstore Management System

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = bookstore
SOURCE = bookstore.c

# Default target
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

# Clean compiled files
clean:
	del /Q $(TARGET).exe 2>nul || rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
