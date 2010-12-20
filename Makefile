CC = gcc

OBJS = jack.o error.o token.o parse.o test.o
PROG = jack
INSTALLDIR = /usr/local/bin

jack:  CFLAGS = -O3
debug: CFLAGS = -Wall -pedantic -std=c99 -ansi -DDEBUG -g -O0 -ggdb3 -Wextra -Wno-missing-field-initializers
small: CFLAGS = -Os

jack: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $(PROG) $(OBJS)

debug: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $(PROG) $(OBJS)
	@ touch debug

small: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $(PROG) $(OBJS)
	@ touch small

clean:
	rm -f debug small $(PROG) $(OBJS)

install:
	cp $(PROG) $(INSTALLDIR)

clobber:
	cd $(INSTALLDIR); rm -f $(PROG)

all: jack install

