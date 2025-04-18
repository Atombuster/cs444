# Variables
CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = semlimit

# Build the executable
$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o

# Build the object file
$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

# Clean up build files
clean:
	rm -f $(TARGET) $(TARGET).o
