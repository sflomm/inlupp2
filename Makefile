CC = gcc
FLAGS = -g -Wall -Wextra --coverage
PFLAGS = -g -Wall -Wextra -pg
OBJECTS = hash_table_iterator.o hash_table.o linked_list.o list_iterator.o webstore_backend.o
COV = webstore_backend.gcda 

vpath %.c generic_utils	
vpath %.c business_logic
vpath %.c tests

# all: webstore_backend_tests
# 	./webstore_backend_tests

%.o: %.c
	$(CC) $(FLAGS) $< -c

%_tests: $(OBJECTS) %_tests.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

test: webstore_backend_tests
	./webstore_backend_tests

# valgrind_webstoreback: webstore_backend_tests
# 	valgrind --leak-check=full ./webstore_backend_tests

# valgrind: webstore_backend_tests
# 	valgrind --leak-check=full ./webstore_backend_tests

# webstoreback_cov: webstore_backend_tests
# 	make $<
# 	gcov -b $(COV)
# 	gcovr $(COV)

# cov: 
# 	make webstoreback_cov

clean:
	rm -f *.o
	rm -f test
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.c.gcov

.PHONY: all test clean all