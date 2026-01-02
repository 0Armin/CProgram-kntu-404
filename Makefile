# Compiler
CC = gcc


# Compiler flags
CFLAGS = -Wall -g


# Source files
SRC = main.c Cell-Sheet/CellSheet.c File/File.c Formula/Formula.c


# Object files
OBJ = $(SRC:.c=.o)


# Executable
TARGET = myprogram


# Default target
all: $(TARGET)


# Link object files into executable
$(TARGET): $(OBJ)
$(CC) $(CFLAGS) -o $@ $^


# Compile .c into .o
%.o: %.c
$(CC) $(CFLAGS) -c $< -o $@


# Clean object files and executable
clean:
rm -f $(OBJ) $(TARGET)