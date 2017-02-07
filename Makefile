
CC = cl
CFLAGS = /Wall /WX /wd4710
SRC = main.c bstree.c

all: 
	$(CC) $(CFLAGS) main.c

list_tester:
	$(CC) $(CFLAGS) list_tester.c list.c custom_mem.c
	list_tester.exe

bstree_tester:
	$(CC) $(CFLAGS) bstree_tester.c bstree.c custom_mem.c
	bstree_tester.exe

string_tester:
	$(CC) $(CFLAGS) string_tester.c string.c custom_mem.c
	string_tester.exe


