CC = gcc
CFLAGS = -Wall -std=c99

SRC = dcooke_analyzer.c
EXECUTABLE = dcooke_analyzer

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXECUTABLE)
