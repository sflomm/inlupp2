#include <CUnit/Basic.h>
#include "../generic_types/hash_table.h"
#include "../generic_types/hash_table_iterator.h"
#include "../generic_types/linked_list.h"
#include "../generic_types/list_iterator.h"
#include "../business_logic/webstore_backend.h"
#include "../business_logic/webstore_types.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

static bool string_eq(elem_t a, elem_t b)
{
   if (a.s == NULL || b.s == NULL) {
        return a.s == b.s;
    }
    return strcmp(a.s, b.s) == 0;
}

static size_t string_knr_hash(elem_t key)
{
  if (key.s == NULL) {
        return 0;
    }
  char *str = key.s;
  size_t result = 0;
  while (*str != '\0')
  {
    result = result * 31 + ((unsigned char) *str);
    str++;
  }
  return result;
}

int init_suite(void) {
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void) {
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

// These are example test functions. You should replace them with
// functions of your own.

void test_create_destroy()
{
    warehouse_t *warehouse = warehouse_create();
    CU_ASSERT_PTR_NOT_NULL(warehouse)
    warehouse_destroy(warehouse);
}

void test_add_1_merch() {
warehouse_t *warehouse = warehouse_create();
  warehouse_add_merch(warehouse, "Bohnanza", "Epic board game", 200);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(warehouse->merch_ht, string_elem("Bohnanza")));
  warehouse_destroy(warehouse);
}
 
void test_add_several_merch() {
    warehouse_t *warehouse = warehouse_create();
    warehouse_add_merch(warehouse, "Bohnanza", "Epic board game", 200);
    warehouse_add_merch(warehouse, "Catan", "Epic board game", 150);
    warehouse_add_merch(warehouse, "Small World", "Epic board game", 300);
    CU_ASSERT_TRUE(ioopm_hash_table_has_key(warehouse->merch_ht, string_elem("Bohnanza")));
    CU_ASSERT_TRUE(ioopm_hash_table_has_key(warehouse->merch_ht, string_elem("Catan")));
    CU_ASSERT_TRUE(ioopm_hash_table_has_key(warehouse->merch_ht, string_elem("Small World")));
    warehouse_destroy(warehouse);
} 

void test_remove_merch() {
  warehouse_t *warehouse = warehouse_create();
  warehouse_add_merch(warehouse, "Bohnanza", "Epic board game", 200);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(warehouse->merch_ht, string_elem("Bohnanza")));
  warehouse_remove_merch(warehouse, "Bohnanza");
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(warehouse->merch_ht, string_elem("Bohnanza")));
  warehouse_destroy(warehouse);
} 

void test_find_merch()
{
  warehouse_t *warehouse = warehouse_create();
  warehouse_add_merch(warehouse, "Catan", "Catan game", 400);
  warehouse_add_merch(warehouse, "Small World", "Small world game", 300);
  warehouse_add_merch(warehouse, "Bohnanza", "Bohnanza game", 200);
  merch_t *merch = warehouse_find_merch(warehouse, "Bohnanza");
  merch_t *merch2 = warehouse_find_merch(warehouse, "Chess");
  CU_ASSERT_PTR_NULL(merch2);

  char *name = merch->name;
  char *desc = merch->desc;
  size_t price = merch->price;
  size_t actual_price = 200;

  CU_ASSERT_EQUAL(price, actual_price);
  CU_ASSERT_EQUAL(name, "Bohnanza");
  CU_ASSERT_EQUAL(desc, "Bohnanza game");
  
  warehouse_destroy(warehouse);
}

void test_edit_merch() {
  warehouse_t *warehouse = warehouse_create();

  // case 1, only new description and price 
  warehouse_add_merch(warehouse, "Bohnanza", "Epic board game", 200);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(warehouse->merch_ht, string_elem("Bohnanza")));
  size_t new_price = 1000;
  warehouse_edit_merch(warehouse, "Bohnanza", "Bohnanza", "New Description", new_price);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(warehouse->merch_ht, string_elem("Bohnanza")));
  merch_t *merch = warehouse_find_merch(warehouse, "Bohnanza");

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(warehouse->merch_ht, string_elem("Bohnanza")));
  CU_ASSERT_TRUE(strcmp(merch->name, "Bohnanza") == 0);
  CU_ASSERT_TRUE(strcmp(merch->desc, "New Description") == 0);
  CU_ASSERT_TRUE(merch->price == new_price);
  // CU_ASSERT_TRUE(strcmp(merch->desc, "Epic board game") == 0);
  // CU_ASSERT_TRUE(merch->price == 200);


  // case 2, new name
  // TODO: check stock in a later test to see that it is unchanged

  // CU_ASSERT_FALSE(ioopm_hash_table_has_key(warehouse->merch_ht, string_elem("Bohnanza")));

  // ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(warehouse->merch_ht);
  // elem_t merch_value = ioopm_hash_table_iterator_current_value(it);
  // elem_t merch_key = ioopm_hash_table_iterator_current_key(it);
  // merch_t *merch = merch_value.p;
  // char *name = merch->name;
  // char *desc = merch->desc;
  // size_t price = merch->price;
  // size_t actual_price = 200;

  // CU_ASSERT_TRUE(string_eq(merch_key, string_elem("Small World")));
  // CU_ASSERT_TRUE(strcmp(desc, "New Description") == 0);
  // CU_ASSERT_TRUE(strcmp(name, "Small World") == 0);
  // CU_ASSERT_TRUE(price == actual_price);
  
  warehouse_destroy(warehouse);
}

// void test_replenish_stock()
// {
//   warehouse_t *warehouse = warehouse_create();
//   warehouse_add_merch(warehouse, "Bohnanza", "Epic board game", 200);
// }


// test_create_empty_() {
//   warehouse_t *warehouse = warehouse_create();
//   ioopm_hash_table_t *cart = warehouse_create_cart(warehouse);
//   CU_ASSERT_TRUE(ioopm_hash_table_is_empty(cart));

// }


// // }

// void test_add_to_cart() {
//   warehouse_t *warehouse = warehouse_create();
//   warehouse_create_cart();
//   warehouse_add_to_cart();
//   warehouse_remove_cart();
// }

// void test_add_to_cart() {
//   warehouse_t *warehouse = warehouse_create();
//   warehouse_create_cart();
//   warehouse_add_to_cart();
//   warehouse_remove_cart();
// }




int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("Test suite", init_suite, clean_suite);
  if (my_test_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
    (CU_add_test(my_test_suite, "create and destroy", test_create_destroy) == NULL) ||
    (CU_add_test(my_test_suite, "add 1 merch", test_add_1_merch) == NULL) ||
    (CU_add_test(my_test_suite, "add several merch", test_add_several_merch) == NULL) ||
    (CU_add_test(my_test_suite, "remove merch", test_remove_merch) == NULL) ||
    (CU_add_test(my_test_suite, "find merch", test_find_merch) == NULL) ||
    (CU_add_test(my_test_suite, "edit merch", test_edit_merch) == NULL) ||
    0
  )
    {
      // If adding any of the tests fails, we tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
} 