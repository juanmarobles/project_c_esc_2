
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -O2 -Iinclude
LDFLAGS = -lm

OBJ = src/main.o src/simulador.o src/validaciones.o
TARGET = artemis_leo.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
