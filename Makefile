CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11 -Iinclude

SRC := $(wildcard src/*.c) mini_os.c
OBJ := $(SRC:.c=.o)

TARGET := mini_os

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
