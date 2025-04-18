# Variables
CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = pc
SRC = $(TARGET).c eventbuf.c
OBJ = $(TARGET).o eventbuf.o

# Build the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Build the object files
$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

eventbuf.o: eventbuf.c
	$(CC) $(CFLAGS) -c eventbuf.c

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJ)
