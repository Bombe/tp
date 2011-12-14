
DEST = tp
OBJS = tp.o

CC_OPTS=-Wall -g

.c.o:
	$(CC) $(CC_OPTS) -c -o $@ $<

all: $(DEST)

$(DEST): $(OBJS)
	$(CC) -o $@ $<

clean:
	rm -f $(DEST)
	rm -f $(OBJS)
