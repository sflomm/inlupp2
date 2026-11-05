CC = gcc
GPROF_OPTIONS  = -Wall -Wextra -pedantic -g -pg
FLAGS = -g -Wall -Wextra
PFLAGS = -g -Wall -Wextra -pg
OBJECTS = hash_table_iterator.o hash_table.o linked_list.o list_iterator.o merch_stock.o cart_calc.o
COV = --coverage

vpath %.c generic_utils	
vpath %.c business_logic
vpath %.c tests
vpath %.c user_interface

%.o: %.c
	$(CC) $(FLAGS) $< -c

%_tests: $(OBJECTS) %_tests.c
	$(CC) $(FLAGS) $^ -lcunit -o $@

program: main.o ui.o utils.o $(OBJECTS)
	$(CC) $(FLAGS) $^ -o $@

run: program
	./program

test: webstore_backend_tests
	./webstore_backend_tests

valgrind: webstore_backend_tests
	valgrind --leak-check=full ./webstore_backend_tests

# AI created coverage stuff
COV_DIR     = cov
COV_FLAGS   = $(FLAGS) --coverage -O0
COV_OBJECTS = $(addprefix $(COV_DIR)/, $(OBJECTS))
COV_SRCS    = merch_stock.c cart_calc.c

$(COV_DIR):
	mkdir -p $(COV_DIR)

# Instrumented objects: same sources, same vpath, but with --coverage
$(COV_DIR)/%.o: %.c | $(COV_DIR)
	$(CC) $(COV_FLAGS) -c $< -o $@

$(COV_DIR)/webstore_backend_tests: $(COV_OBJECTS) webstore_backend_tests.c
	$(CC) $(COV_FLAGS) $^ -lcunit -o $@

GCOVR_FLAGS = -r . --object-directory $(COV_DIR) \
              --filter '.*merch_stock\.c' --filter '.*cart_calc\.c'

coverage: $(COV_DIR)/webstore_backend_tests
	rm -f $(COV_DIR)/*.gcda
	./$(COV_DIR)/webstore_backend_tests
	@echo "=== Line coverage ==="
	gcovr $(GCOVR_FLAGS)
	@echo "=== Branch coverage ==="
	gcovr $(GCOVR_FLAGS) --txt-metric branch

# gprof: clean
# 	$(CC) $(GPROF_OPTIONS) generic_utils/freq_count.c generic_utils/hash_table.c generic_utils/hash_table_iterator.c -o freq_new
# 	./freq_new 16k-words.txt
# 	gprof freq_new gmon.out > analysis.txt

clean:
	rm -f *.o webstore_backend_tests
	rm -f *.gcda *.gcno *.c.gcov
	rm -rf $(COV_DIR)

.PHONY: test valgrind coverage clean program