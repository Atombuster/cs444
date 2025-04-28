
.PHONY: all

all: main.o adder.o
	gcc -Wall -Wextra -o main main.o adder.o

main.o: main.c adder.h
	gcc -Wall -Wextra -c main.c

adder.o: adder.c
	gcc -Wall -Wextra -c adder.c


.PHONY: clean

clean:
	rm -f *.o