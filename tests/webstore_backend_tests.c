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

// FIXME: städa bort? 
// static bool string_eq(elem_t a, elem_t b)
// {
//    if (a.s == NULL || b.s == NULL) {
//         return a.s == b.s;
//     }
//     return strcmp(a.s, b.s) == 0;
// }

// static size_t string_knr_hash(elem_t key)
// {
//   if (key.s == NULL) {
//         return 0;
//     }
//   char *str = key.s;
//   size_t result = 0;
//   while (*str != '\0')
//   {
//     result = result * 31 + ((unsigned char) *str);
//     str++;
//   }
//   return result;
// }

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

  // case 2, new name
  warehouse_edit_merch(warehouse, "Bohnanza", "Catan", "New Description", new_price);
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(warehouse->merch_ht, string_elem("Bohnanza")));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(warehouse->merch_ht, string_elem("Catan")));
  merch_t *merch2 = warehouse_find_merch(warehouse, "Catan");
  CU_ASSERT_TRUE(strcmp(merch2->name, "Catan") == 0);
  CU_ASSERT_TRUE(strcmp(merch2->desc, "New Description") == 0);
  CU_ASSERT_TRUE(merch2->price == new_price);

  // case 3, merch does not exist
  warehouse_edit_merch(warehouse, "Yatzy", "Catan", "New Description", new_price);
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(warehouse->merch_ht, string_elem("Yatzy")));
  
  warehouse_destroy(warehouse);
}

void test_replenish_stock()
{
  warehouse_t *warehouse = warehouse_create();
  warehouse_add_merch(warehouse, "Bohnanza", "Epic board game", 200);
  merch_t *merch = warehouse_find_merch(warehouse, "Bohnanza");
  size_t quant_to_add = 2;

  // case 1, shelf does not exist
  warehouse_replenish_stock(warehouse, "A1", merch, quant_to_add);
  CU_ASSERT_EQUAL(merch->stock, quant_to_add);

  ioopm_list_iterator_t *iter = ioopm_list_iterator_create(merch->locs);
  bool found = false;

  while (!found && !ioopm_list_iterator_at_end(iter))
  {
    shelf_t *current_shelf = ioopm_list_iterator_current(iter).p;
    if (strcmp(current_shelf->shelf, "A1") == 0)
    {
      found = true;
      CU_ASSERT_TRUE(current_shelf->quant == quant_to_add);
    }
    ioopm_list_iterator_advance(iter); 
  }

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(warehouse->location_ht, string_elem("A1")));
  CU_ASSERT_TRUE(found);
  ioopm_list_iterator_destroy(iter);

  // case 2, shelf already exists 
  size_t more_quant = 4; 
  warehouse_replenish_stock(warehouse, "A1", merch, more_quant);
  CU_ASSERT_EQUAL(merch->stock, more_quant + quant_to_add);

  ioopm_list_iterator_t *iter2 = ioopm_list_iterator_create(merch->locs);
  bool found2 = false;

  while (!found2 && !ioopm_list_iterator_at_end(iter2))
  {
    shelf_t *current_shelf = ioopm_list_iterator_current(iter2).p;
    if (strcmp(current_shelf->shelf, "A1") == 0)
    {
      found2 = true;
      CU_ASSERT_TRUE(current_shelf->quant == more_quant + quant_to_add);
    }
    ioopm_list_iterator_advance(iter2); 
  }

  CU_ASSERT_TRUE(found);
  ioopm_list_iterator_destroy(iter2);

  warehouse_destroy(warehouse);
}

void test_edit_merch_same_stock()
{
  warehouse_t *warehouse = warehouse_create();
  warehouse_add_merch(warehouse, "Bohnanza", "Epic board game", 200);
  size_t new_price = 1000;
  warehouse_edit_merch(warehouse, "Bohnanza", "Catan", "New Description", new_price);
  merch_t *merch = warehouse_find_merch(warehouse, "Catan");
  size_t add_quant = 10;
  warehouse_replenish_stock(warehouse, "B8", merch, add_quant); 
  CU_ASSERT_EQUAL(merch->stock, add_quant);

  warehouse_destroy(warehouse);
}

// test_create_empty_() {
//   warehouse_t *warehouse = warehouse_create();
//   ioopm_hash_table_t *cart = warehouse_create_cart(warehouse);
//   CU_ASSERT_TRUE(ioopm_hash_table_is_empty(cart));

// }


// // }

void test_add_to_cart() {
  //initilazing
  size_t index = 0;
  warehouse_t *warehouse = warehouse_create();
  shopping_cart_t *cart = warehouse_create_cart(warehouse);
  warehouse_add_merch(warehouse, "Bohnanza", "Epic board game", 200);
    size_t add_quant = 10;
    merch_t *merch = warehouse_find_merch(warehouse, "Bohnanza");
  warehouse_replenish_stock(warehouse, "A10", merch, add_quant);
  //add to cart
  warehouse_add_to_cart(warehouse, cart->id, "Bohnanza", 10);
  
  elem_t result = size_elem(0);
  ioopm_hash_table_lookup(cart->items, string_elem("Bohnanza"), &result);
  CU_ASSERT_EQUAL(result.si, 10);

  //remove from cart and destroy the warehouse
  warehouse_remove_cart(warehouse, cart->id, &index);
  warehouse_destroy(warehouse);
}

void test_add_several_to_cart() {
  size_t index = 0;
  warehouse_t *warehouse = warehouse_create();
  shopping_cart_t *cart = warehouse_create_cart(warehouse);
  warehouse_add_merch(warehouse, "Bohnanza", "Epic board game", 200);
  warehouse_add_merch(warehouse, "Catan", "Epic board game", 200);
  warehouse_add_merch(warehouse, "Small World", "Epic board game", 200);
  size_t add_quant = 10;
  merch_t *merch1 = warehouse_find_merch(warehouse, "Bohnanza");
  merch_t *merch2 = warehouse_find_merch(warehouse, "Catan");
  merch_t *merch3 = warehouse_find_merch(warehouse, "Small World");
  warehouse_replenish_stock(warehouse, "A10", merch1, add_quant);
  warehouse_replenish_stock(warehouse, "A11", merch2, add_quant);
  warehouse_replenish_stock(warehouse, "A12", merch3, add_quant);

  //add to cart
   warehouse_add_to_cart(warehouse, cart->id, "Bohnanza", add_quant);
   warehouse_add_to_cart(warehouse, cart->id, "Catan", add_quant);
   warehouse_add_to_cart(warehouse, cart->id, "Small World", add_quant);
   ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(cart->items);


   while (!ioopm_hash_table_iterator_at_end(it)) {
   CU_ASSERT_EQUAL(ioopm_hash_table_iterator_current_value(it).si, add_quant);
   ioopm_hash_table_iterator_advance(it);
   }
   ioopm_hash_table_iterator_destroy(it);

   warehouse_remove_cart(warehouse, cart->id, &index);
}





void test_remove_from_cart() {
   warehouse_t *warehouse = warehouse_create();
  shopping_cart_t *cart = warehouse_create_cart(warehouse);
  size_t index = 0;
  warehouse_add_merch(warehouse, "Bohnanza", "Epic board game", 200);
  size_t add_quant = 10;
  merch_t *merch1 = warehouse_find_merch(warehouse, "Bohnanza");
  warehouse_replenish_stock(warehouse, "A10", merch1, add_quant);

    //add to cart
   warehouse_add_to_cart(warehouse, cart->id, "Bohnanza", add_quant);
   //remove from cart
   warehouse_remove_from_cart(warehouse, cart->id, "Bohnanza", add_quant);

   CU_ASSERT_FALSE(ioopm_hash_table_has_key(cart->items, string_elem("Bohnanza")));

   //free memory
   warehouse_remove_cart(warehouse, cart->id, &index);
   warehouse_destroy(warehouse);
}

void test_remove_several_from_cart() {
   warehouse_t *warehouse = warehouse_create();
  shopping_cart_t *cart = warehouse_create_cart(warehouse);
  size_t index = 0;
  warehouse_add_merch(warehouse, "Bohnanza", "Epic board game", 200);
  warehouse_add_merch(warehouse, "Catan", "Epic board game", 200);
  warehouse_add_merch(warehouse, "Small World", "Epic board game", 200);
  size_t add_quant = 10;
  size_t add_quant_2 = 8;
  size_t add_quant_3 = 7;
  merch_t *merch1 = warehouse_find_merch(warehouse, "Bohnanza");
  merch_t *merch2 = warehouse_find_merch(warehouse, "Catan");
  merch_t *merch3 = warehouse_find_merch(warehouse, "Small World");
  warehouse_replenish_stock(warehouse, "A10", merch1, add_quant);
  warehouse_replenish_stock(warehouse, "A11", merch2, add_quant);
  warehouse_replenish_stock(warehouse, "A12", merch3, add_quant);

    //add to cart
   warehouse_add_to_cart(warehouse, cart->id, "Bohnanza", add_quant);
   warehouse_add_to_cart(warehouse, cart->id, "Catan", add_quant);
   warehouse_add_to_cart(warehouse, cart->id, "Small World", add_quant);
   //remove from cart
   warehouse_remove_from_cart(warehouse, cart->id, "Bohnanza", add_quant);
   warehouse_remove_from_cart(warehouse, cart->id, "Catan", add_quant_2);
   warehouse_remove_from_cart(warehouse, cart->id, "Small World", add_quant_3);

   ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(cart->items);

   //removing with the same quantity removes the entire key from ht
   CU_ASSERT_FALSE(ioopm_hash_table_has_key(cart->items, string_elem("Bohnanza")));
   //removing with a different quant inserts the difference between old and new quant.
   elem_t result;
   ioopm_hash_table_lookup(cart->items, string_elem("Catan"), &result);
   CU_ASSERT_EQUAL(result.si, 2);
   ioopm_hash_table_lookup(cart->items, string_elem("Small World"), &result);
   CU_ASSERT_EQUAL(result.si, 3);
   ioopm_hash_table_iterator_destroy(it);


   //free memory
   warehouse_remove_cart(warehouse, cart->id, &index);
   warehouse_destroy(warehouse);
} //FIXME: göra teser för remove_cart funktionen  
void test_remove_cart() {
  size_t index = 0;
  warehouse_t *warehouse = warehouse_create();
  shopping_cart_t *cart = warehouse_create_cart(warehouse);
  size_t cart_id = cart->id;
  warehouse_remove_cart(warehouse, cart->id, &index);
  CU_ASSERT_EQUAL(warehouse_find_shopping_cart(warehouse, cart_id, &index), NULL);
  warehouse_destroy(warehouse);
}

void test_checkout_merch() {
  size_t index = 0;
  warehouse_t *warehouse = warehouse_create();
  shopping_cart_t *cart = warehouse_create_cart(warehouse);
  size_t add_quant = 10;
  size_t add_quant_2 = 8;
  size_t add_quant_3 = 7;
  // add and find merch
  warehouse_add_merch(warehouse, "Bohnanza", "Epic board game", 200);
  warehouse_add_merch(warehouse, "Catan", "Epic board game", 200);
  warehouse_add_merch(warehouse, "Small World", "Epic board game", 200);
  merch_t *merch1 = warehouse_find_merch(warehouse, "Bohnanza");
  merch_t *merch2 = warehouse_find_merch(warehouse, "Catan");
  merch_t *merch3 = warehouse_find_merch(warehouse, "Small World");

  warehouse_replenish_stock(warehouse, "A10", merch1, add_quant);
  warehouse_replenish_stock(warehouse, "A11", merch2, add_quant);
  warehouse_replenish_stock(warehouse, "A12", merch3, add_quant);

  warehouse_add_to_cart(warehouse, cart->id, "Bohnanza", add_quant);
  warehouse_add_to_cart(warehouse, cart->id, "Catan", add_quant_2);
  warehouse_add_to_cart(warehouse, cart->id, "Small World", add_quant_3);
  size_t cart_id = cart->id;

  warehouse_checkout(warehouse, cart->id);
  CU_ASSERT_EQUAL(merch1->stock, 0);
  CU_ASSERT_EQUAL(merch2->stock, 2);
  CU_ASSERT_EQUAL(merch3->stock, 3);
  CU_ASSERT_EQUAL(warehouse_find_shopping_cart(warehouse, cart_id, &index), NULL);
  warehouse_destroy(warehouse);
}

void test_calculate_cost() {
  size_t index = 0;
  warehouse_t *warehouse = warehouse_create();
  shopping_cart_t *cart = warehouse_create_cart(warehouse);
  size_t add_quant = 10;
  size_t add_quant_2 = 8;
  size_t add_quant_3 = 7;

  warehouse_add_merch(warehouse, "Bohnanza", "Epic board game", 200);
  warehouse_add_merch(warehouse, "Catan", "Epic board game", 100);
  warehouse_add_merch(warehouse, "Small World", "Epic board game", 50);
  merch_t *merch1 = warehouse_find_merch(warehouse, "Bohnanza");
  merch_t *merch2 = warehouse_find_merch(warehouse, "Catan");
  merch_t *merch3 = warehouse_find_merch(warehouse, "Small World");

  warehouse_replenish_stock(warehouse, "A10", merch1, add_quant);
  warehouse_replenish_stock(warehouse, "A11", merch2, add_quant);
  warehouse_replenish_stock(warehouse, "A12", merch3, add_quant);

  warehouse_add_to_cart(warehouse, cart->id, "Bohnanza", add_quant);
  warehouse_add_to_cart(warehouse, cart->id, "Catan", add_quant_2);
  warehouse_add_to_cart(warehouse, cart->id, "Small World", add_quant_3);

  size_t cost = warehouse_calculate_cost(warehouse, cart->id);
  CU_ASSERT_EQUAL(cost, 3150);
  warehouse_remove_cart(warehouse, cart->id, &index);
  warehouse_destroy(warehouse);
}




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
    (CU_add_test(my_test_suite, "replenish stock", test_replenish_stock) == NULL) ||
    (CU_add_test(my_test_suite, "edit merch and replenish stock, check stock property", test_edit_merch_same_stock) == NULL) ||
    (CU_add_test(my_test_suite, "add to cart", test_add_to_cart) == NULL) ||
    (CU_add_test(my_test_suite, "add several to cart", test_add_several_merch) == NULL) ||
    (CU_add_test(my_test_suite, "remove from cart", test_remove_from_cart) == NULL) ||
    (CU_add_test(my_test_suite, "remove several from cart", test_remove_several_from_cart) == NULL) ||
    (CU_add_test(my_test_suite, "remove from cart", test_remove_cart) == NULL) ||
    (CU_add_test(my_test_suite, "checkout merch", test_checkout_merch) == NULL) ||
    (CU_add_test(my_test_suite, "calculate cost", test_calculate_cost) == NULL) ||
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