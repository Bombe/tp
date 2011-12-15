
DEST = tp
OBJS = Formatter.o Copier.o CopierListener.o Main.o

CC = g++
CC_OPTS=-Wall -g

.cpp.o:
	$(CC) $(CC_OPTS) -c -o $@ $<

all: $(DEST)

Formatter.o: Formatter.hpp
CopierListener.o: CopierListener.cpp Copier.hpp
Copier.o: Copier.cpp CopierListener.hpp
Main.o: Main.cpp Copier.hpp CopierListener.hpp Formatter.hpp

$(DEST): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm -f $(DEST)
	rm -f $(OBJS)
