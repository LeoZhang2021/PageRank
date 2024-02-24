RM = rm -f
CC = gcc
CFLAGS = -std=c99 -g -pthread

default: all

all: pagerank

pagerank: pagerank.c prhelper.c
	$(CC) $(CFLAGS) -o $@ pagerank.c prhelper.c

clean:
	$(RM) pagerank

.PHONY: pagerank
