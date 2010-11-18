CC=gcc

CFLAGS_REL = -O3
CFLAGS_DBG = -Wall -pedantic -std=c99 -ansi -DDEBUG -g -O0 -ggdb3 -Wextra -Wno-missing-field-initializers
CFLAGS_SML = -Os

OBJS = jack.c error.c token.c parse.c test.c
OUT  = jack

default: release

release: $(OBJS)
	$(CC) $(CFLAGS_REL) $(LIBS) -o $(OUT) $^ 

debug: $(OBJS)
	$(CC) $(CFLAGS_DBG) $(LIBS) -o $(OUT) $^

small: $(OBJS)
	$(CC) $(CFLAGS_SML) $(LIBS) -o $(OUT) $^

clean:
	rm -f $(OUT)
