CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = pqueue.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = dispatch_students
TESTFILES = $(shell ls ./input)

.PHONY: clean

all: $(TARGET)

test: $(TARGET) $(TESTFILES)

%.in:
	./$(TARGET) ./input/$*.in


$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)