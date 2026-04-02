CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -O2
LIBS = -lm

BIN = twixt_engine
OBJ = main.o engine.o render.o cmd.o

all: $(BIN)

$(BIN): $(OBJ)
	@echo "Linking $(BIN)..."
	$(CC) $(OBJ) -o $(BIN) $(LIBS)

%.o: %.c proto.h
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning workspace..."
	rm -f $(OBJ) $(BIN)

rebuild: clean all

.PHONY: all clean rebuild