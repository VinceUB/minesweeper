CC := cc

SRC := $(wildcard src/*.c)
OUT := $(patsubst src/%.c, out/%.o, $(SRC))

out/%.o: src/%.c
	$(CC) -c -o $@ $^

minesweeper: $(OUT)
	$(CC) -o minesweeper $^