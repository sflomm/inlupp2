CC = gcc
GPROF_OPTIONS  = -Wall -Wextra -pedantic -g -pg
FLAGS = -g -Wall -Wextra --coverage
OBJECTS = hash_table_iterator.o hash_table.o linked_list.o list_iterator.o merch_stock.o ui.o
# add cart_calc.o ^
# COV = linked_list.gcda list_iterator.gcda hash_table.gcda hash_table_iterator.gcda 
PFLAGS = -g -Wall -Wextra -pg
COV = webstore_backend.gcda 

vpath %.c generic_utils	
vpath %.c business_logic
vpath %.c tests
vpath %.c user_interface

# all: webstore_backend_tests
# 	./webstore_backend_tests

%.o: %.c
	$(CC) $(FLAGS) $< -c

%_tests: $(OBJECTS) %_tests.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

program: main.o ui.o $(OBJECTS)
	$(CC) $(FLAGS) $^ -o $@

run: program
	./program

test: webstore_backend_tests
	./webstore_backend_tests

valgrind: webstore_backend_tests
	valgrind --leak-check=full ./webstore_backend_tests

COV_TARGET = merch_stock

coverage: webstore_backend_tests
	rm -f *.gcda *.gcov
	./webstore_backend_tests
	gcov -b $(COV_TARGET).o
	gcovr -r . --filter '.*$(COV_TARGET)\.c' --txt-metric branch

# gprof: clean
# 	$(CC) $(GPROF_OPTIONS) generic_utils/freq_count.c generic_utils/hash_table.c generic_utils/hash_table_iterator.c -o freq_new
# 	./freq_new 16k-words.txt
# 	gprof freq_new gmon.out > analysis.txt

clean:
	rm -f *.o webstore_backend_tests
	rm -f *.gcda *.gcno *.gcov gmon.out

.PHONY: test valgrind coverage clean program