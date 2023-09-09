CC=gcc
CFLAGS=-Wall -pthread

all: bounded_buffer bounded_waiting

bounded_buffer: bounded_buffer.c
	$(CC) $(CFLAGS) -o bounded_buffer bounded_buffer.c

bounded_waiting: bounded_waiting.c
	$(CC) $(CFLAGS) -o bounded_waiting bounded_waiting.c

clean:
	rm -f bounded_buffer bounded_waiting
