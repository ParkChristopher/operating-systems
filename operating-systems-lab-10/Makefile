# variables
EXE=lab10
CC=gcc
CFLAGS=-ggdb -Wall -std=gnu99 -pedantic 
#-W(warnings) 
#-pedantic ( conform to standards!!! )
#-std=c99 means use the c99 standard
LFLAGS=
SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
DEPS:=$(patsubst %.c,%.d,$(SRCS))

# link step
$(EXE): $(DEPS) $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LFLAGS)

# $< means the %.c  
%.d: %.c
	$(CC) $(CFLAGS) -M $< > $@
	$(CC) $(CFLAGS) -M $< | sed s/\\.o/.d/ >> $@

clean:
	rm -f $(OBJS) $(DEPS) 

valgrind:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./$(EXE)

-include $(DEPS)
