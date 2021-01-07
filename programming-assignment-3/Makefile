
CC = gcc
CFLAGS = -g -pthread
# LFLAGS = -Wall -Wextra

all: multi-lookup

multi-lookup:
	$(CC) $(CFLAGS) -o multi-lookup multi-lookup.c util.c queue.c

clean:
	rm -f multi-lookup
	rm serviced.txt
	rm results.txt
	rm performance.txt
