
.PHONY: all clean pristine test

CC = gcc
CFLAGS = -Wall -Wextra -Werror
TEST_CFLAGS =$(CFLAGS) -DCTEST_ENABLE

all: testfs.o libvvsfs.a
	$(CC) $(CFLAGS) -o testfs testfs.o -L. -lvvsfs

libvvsfs.a: image.o block.o
	ar rcs libvvsfs.a image.o block.o

testfs.o: testfs.c block.h
	$(CC) $(CFLAGS) -c testfs.c

block.o: block.c image.h
	$(CC) $(CFLAGS) -c block.c

image.o: image.c 
	$(CC) $(CFLAGS) -c image.c

test: clean testfs.o libvvsfs.a
	$(CC) $(TEST_CFLAGS) -c testfs.c
	$(CC) $(TEST_CFLAGS) -o testfs testfs.o -L. -lvvsfs
	./testfs

clean:
	rm -f *.o *.txt

pristine: clean
	rm -f testfs libvvsfs.a