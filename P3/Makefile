# variable definition

CC = g++
MAINSRCS = p3.C
OTHSRCS = node.C edge.C graph.C 
TEMPLATESRCS = 
HEADERS = node.h edge.h graph.h
SRCS = $(MAINSRCS) $(OTHSRCS)
OBJS = $(SRCS:.C=.o)
TARGETS = $(MAINSRCS:.C=)
MEMCHECKARGS = < g1.in

CFLAGS = -g -Wall

%.o: %.C
	$(CC) $(CFLAGS) -o $@ -c $< 

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGETS) $(OBJS)

memcheck: $(TARGETS)
	valgrind --leak-check=full ./$(TARGETS) $(MEMCHECKARGS)

clean:
	rm -f $(OBJS) $(TARGETS) tags

tags: $(SRCS) $(HEADERS) $(TEMPLATESRCS)
	ctags $^

.PHONY: all memcheck clean tags
