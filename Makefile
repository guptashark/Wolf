
CC = cl
CFLAGS = /Wall /WX /wd4710
SRC = main.c bstree.c

all: 
	$(CC) $(CFLAGS) $(SRC)

