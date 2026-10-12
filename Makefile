CC = gcc
FLAGS = -g -Wall -Wextra --coverage
PFLAGS = -g -Wall -Wextra -pg
OBJECTS = linked_list.o list_iterator.o hash_table.o hash_table_iterator.o
HCOV = hash_table.gcda hash_table_iterator.gcda
LCOV = linked_list.gcda list_iterator.gcda

SMALL = ./freq_text/small.txt
1k = ./freq_text/1k-long-words.txt
10k = ./freq_text/10k-words.txt
16k = ./freq_text/16k-words.txt

all: linked_list_test hash_table_test
	./linked_list_test && ./hash_table_test

%.o: %.c
	$(CC) $(FLAGS) $< -c

%_test: $(OBJECTS) %_test.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

%_count: $(OBJECTS) %_count.c
	$(CC) $(FLAGS) $^ -o $@

linked_test: linked_list_test
	./linked_list_test

hash_test: hash_table_test
	./hash_table_test

freq: freq_count
	./freq_count $(SMALL)

test: linked_list_test hash_table_test
	./linked_list_test 
	./hash_table_test

valgrind_list: linked_list_test
	valgrind --leak-check=full ./linked_list_test

valgrind_hash: hash_table_test
	valgrind --leak-check=full ./hash_table_test

valgrind_freq: freq_count
	valgrind --leak-check=full ./freq_count hash_table_struct.h

valgrind: hash_table_test linked_list_test
	valgrind --leak-check=full ./hash_table_test
	valgrind --leak-check=full ./linked_list_test

hash_cov: hash_test
	make $<
	gcov -b $(HCOV)
	gcovr $(HCOV)


linked_cov: linked_test
	make $<
	gcov -b $(LCOV)
	gcovr $(LCOV)

freq_prof: hash_table.c hash_table_iterator.c freq_count
	$(CC) $(PFLAGS) hash_table.c hash_table_iterator.c -c
	$(CC) $(PFLAGS) hash_table.o hash_table_iterator.o freq_count.c -o freq_count

freq_small: 
	make freq_prof
	./freq_count $(SMALL)
	gprof ./freq_count > small.gprof

freq_1k:
	make freq_prof
	./freq_count $(1k)
	gprof ./freq_count > 1k.gprof


freq_10k:
	make freq_prof
	./freq_count $(10k)
	gprof ./freq_count > 10k.gprof

freq_16k: 
	make freq_prof
	./freq_count $(16k)
	gprof ./freq_count > 16k.gprof

cov: 
	make hash_cov
	make linked_cov

clean:
	rm -f *.o
	rm -f test
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.c.gcov

.PHONY: 
	test hash_test linked_test freq
	valgrind valgrind_hash valgrind_list valgrind_freq 
	hash_cov linked_cov cov
	clean all