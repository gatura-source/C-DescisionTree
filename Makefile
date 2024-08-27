# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -g

# Target executable
TARGET = cart

# Source files
SRCS = main.c utils.c tokenizer.c

# Object files (derived from source files)
OBJS = $(SRCS:.c=.o)

# Header files
DEPS = main.h

# Default target (first target in the Makefile)
all: $(TARGET)

# Rule for linking object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule for compiling .c files into .o files
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

# .PHONY to avoid conflicts with files named 'clean' or 'all'
.PHONY: all clean
