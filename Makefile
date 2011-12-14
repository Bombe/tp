
DEST = tp
OBJS = tp.o Formatter.o

CC = g++
CC_OPTS=-Wall -g

.cpp.o:
	$(CC) $(CC_OPTS) -c -o $@ $<

all: $(DEST)

tp.o: tp.cpp Formatter.hpp

$(DEST): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(DEST)
	rm -f $(OBJS)
