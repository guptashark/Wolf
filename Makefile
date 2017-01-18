
CC = cl
CFLAGS = /Wall /WX /wd4710
SRC = main.c bstree.c

bstree_test:
	$(CC) $(CFLAGS) bstree.c bstree_tester.c custom_mem.c

all: 
	$(CC) $(CFLAGS) $(SRC)


