CPPFLAGS = -I../include
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
OBJS = stack.o stack_test.o
SOURCES =  stack.c ../test/stack_test.c
DEBUG = -g
RELEASE = -DNDEBUG -O3
TARGET = stack.out

all: debug
	
stack.o: stack.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c stack.c

stack_test.o: ../test/stack_test.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c ../test/stack_test.c	
  
debug: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEBUG) -o $(TARGET) $(SOURCES)

release: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(RELEASE) -o $(TARGET) $(SOURCES)

.PHONY: clean all

clean:
	rm -f stack*.o stack*.a $(TARGET)
	
lib.ar:
	ar r stack.a $(OBJS)
