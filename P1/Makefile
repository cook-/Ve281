# variable definition

CC = g++
MAINSRCS = p1.C
OTHSRCS =
TEMPLATESRCS = queue.C
HEADERS = queue.h p1.h
SRCS = $(MAINSRCS) $(OTHSRCS)
OBJS = $(SRCS:.C=.o)
TARGETS = $(MAINSRCS:.C=)

CFLAGS = -g -Wall

%.o: %.C
	$(CC) $(CFLAGS) -o $@ -c $< 

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS)

memcheck: $(TARGETS)
	valgrind --leak-check=full ./$(TARGETS) grid.txt

clean:
	rm -f $(OBJS) $(TARGETS) tags

tags: $(SRCS) $(HEADERS) $(TEMPLATESRCS)
	ctags $^

.PHONY: all memcheck clean tags
