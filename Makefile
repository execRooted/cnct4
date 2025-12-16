CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lncurses

TARGET = cnct4
SRCS = main.c board.c ai.c
HEADERS = game.h board.h ai.h

$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: clean