CC = gcc

CFLAGS = -Wall -Wextra -O2

TARGET = lolfetch

SRCS = lolfetch.c blockart.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

rebuild: clean all

.PHONY: all clean rebuild
