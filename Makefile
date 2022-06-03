CC = gcc
CFLAGS  = -std=c11 -Wall -Wextra -pedantic

SRCS = test.c memory.h symbol.h memory.c symbol.c
OBJS = $(SRCS:.c=.o)

default: all

MAIN = mycc
all:   $(OBJS)
	$(CC) $(CFLAGS) -o all $(OBJS) $(CFLAGS)

clean:
	$(RM) all *.o *~
