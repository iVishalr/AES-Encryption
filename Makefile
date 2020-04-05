CC=gcc
CFLAGS=-c -Wall
all: start
start: AES128.o
	$(CC) AES128.o
AESEncrypt.o: AES128.c
	$(CC) $(CFLAGS) AES128.c
clean: 
	rm -rf *o a.out
