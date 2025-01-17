CC = gcc
CFLAGS = -Wall -Iinclude -w

all: httpx
httpx: src/*.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f httpx
