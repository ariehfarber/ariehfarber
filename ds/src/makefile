CPPFLAGS = -I../include
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
OBJS = bitarray.o bitarray_test.o
SOURCES =  bitarray.c ../test/bitarray_test.c
DEBUG = -g
RELEASE = -DNDEBUG -O3
TARGET = bitarray.out

all: debug
	
bitarray.o: bitarray.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c bitarray.c

bitarray_test.o: ../test/bitarray_test.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c ../test/bitarray_test.c	
  
debug: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEBUG) -o $(TARGET) $(SOURCES)

release: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(RELEASE) -o $(TARGET) $(SOURCES)

.PHONY: clean all

clean:
	rm -f bitarray*.o bitarray*.a $(TARGET)
	
lib.ar:
	ar r bitarray.a $(OBJS)
