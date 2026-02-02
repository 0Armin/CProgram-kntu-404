CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = main.c \
      sheet_init.c \
      sheet_resize.c \
      sheetaccess.c \
      sheeterror.c \
      sheetprint.c \
      sheetvalidate.c

OBJ = $(SRC:.c=.o)

TARGET = sheet_app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c sheet.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)

run: all
	./$(TARGET)