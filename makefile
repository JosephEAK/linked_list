CC ?= gcc
CFLAGS += -Wall --pedantic -g 
LIB_PATH = .

all: clean lib
	$(CC) $(LDFLAGS) -L$(LIB_PATH) -o list $(CFLAGS) main.c -lcunit -llist

lib:
	$(CC) -fPIC -c linked_list_function.c
	$(CC) -shared -o liblist.so linked_list_function.o -lcunit
valgrind:
	make test && valgrind --leak-check=yes ./test_list
test_debug: clean lib
	$(CC) $(LDFLAGS) -L$(LIB_PATH) -o test_list $(CFLAGS) $(DEBUG_FLAGS) test_linked_list_function.c linked_list_function.c -llist -lcunit 
clean:
	rm -f *.o list test_list *.so
.PHONY: test