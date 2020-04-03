CC=gcc
CFLAGS=-c -Wall
all: start
start: AESEncrypt.o
	$(CC) AESEncrypt.o
AESEncrypt.o: AESEncrypt.c
	$(CC) $(CFLAGS) AESEncrypt.c
clean: 
	rm -rf *o a.out
