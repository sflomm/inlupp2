#include <CUnit/Basic.h>
#include <string.h>
#include "../generic_types/hash_table.h"
#include "../generic_types/hash_table_struct.h"
#include "../generic_types/hash_table_iterator.h"

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

// Hash functions & equality functions

// Int keys
size_t simple_int_hash(elem_t key)
{
  return key.i;
}

bool simple_int_eq(elem_t key1, elem_t key2)
{
  return (key1.i == key2.i);
}

// Bool keys
size_t simple_bool_hash(elem_t key)
{
  if (false == key.b)
  {
    return 0;
  }
  else 
  {
    return 1;
  }
}

bool simple_bool_eq(elem_t key1, elem_t key2)
{
  return (key1.b == key2.b);
}

// Pointer keys
size_t simple_ptr_hash(elem_t key)
{
  return (size_t) key.p;
}

bool simple_ptr_eq(elem_t key1, elem_t key2)
{
  return (key1.p) == (key2.p);
}

// String keys
size_t string_knr_hash(elem_t key)
{
  char *str = key.s;
  size_t result = 0;
  while (*str != '\0')
  {
    result = result * 31 + ((unsigned char) *str);
    str++;
  }
  return result;
}

bool simple_knr_eq(elem_t key1, elem_t key2)
{
  return (strcmp(key1.s, key2.s) == 0);
}



// Write test functions here

// Checks that result from create is not NULL
void test_create_destroy()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);
   CU_ASSERT_PTR_NOT_NULL(ht);
   ioopm_hash_table_destroy(ht);
}

void test_insert_once()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);

  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);

  // check that key is not in ht
  elem_t result = int_elem(0);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, 0);

  // insert key-value pair and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

void test_insert_twice()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);

  //pair 0
  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);
  // pair 1
  elem_t key1 = string_elem("cba");
  elem_t value1 = int_elem(321);

  // check that keys are not in ht
  elem_t result = int_elem(0);
  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, 0);

  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, key1, &result));
  CU_ASSERT_EQUAL(result.i, 0);

  // insert key-value pairs and check that the mapping exists
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);

  ioopm_hash_table_insert(ht, key1, value1);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key1, &result));
  CU_ASSERT_EQUAL(result.i, value1.i);

  // destroy hash table
  ioopm_hash_table_destroy(ht);
}

// Fråga TA om kompilering med samma sträng (key och key2), pga freqcount.c
void test_update_val()
{
  // create new hash table
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);

  //make og key value pair
  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);

  //initialize lookup result integer
  elem_t key2 = string_elem("abc");
  elem_t result;
  
  //insert key pair value in ht and check that it got inserted correctly
  ioopm_hash_table_insert(ht, key, value);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value.i);
  
  // update value and insert new value to same key
  elem_t value2 = int_elem(321);
  ioopm_hash_table_insert(ht, key2, value2);
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, key, &result));
  CU_ASSERT_EQUAL(result.i, value2.i);

  //destroy hashtable when done
  ioopm_hash_table_destroy(ht);
}

// for future testing: invalid_key or non_existent key?

void test_hash_table_remove()
{
  //create new hashtable
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);

  //make key value pair
  elem_t key = string_elem("abc");
  elem_t value = int_elem(123);

  //insert key-value pair in ht 
  ioopm_hash_table_insert(ht, key, value);
  
  //remove key-value pair
  elem_t result = ioopm_hash_table_remove(ht, key); // should return 123
  CU_ASSERT_EQUAL(result.i, value.i);
  
  //remove same pair again
  result = ioopm_hash_table_remove(ht, key); // should return 0
  CU_ASSERT_NOT_EQUAL(result.i, value.i);
   
  //destroy hashtable when done
  ioopm_hash_table_destroy(ht);
}

// TICKET 2 (2.1) - the 5 different tests

void test_ht_has_key1()
{
  //create new hashtable
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);

  //make key value pair
  elem_t key = string_elem("abc");

  //check if key is in ht
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key));
  
  //destroy hashtable when done
  ioopm_hash_table_destroy(ht);
}

void test_ht_has_key2()
{
  //create new hashtable
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);

  //make key value pair
  elem_t key = string_elem("abc");
  elem_t key2 = string_elem("cba");
  int value = 123;
  
  //insert key-value pair
  ioopm_hash_table_insert(ht, key, int_elem(value));

  //check if key is in ht and if key2 is in ht
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key2));
  
  //destroy hashtable when done
  ioopm_hash_table_destroy(ht);
}

void test_ht_has_key3()
{
  //create new hashtable
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);

  // Make key-value pairs
  elem_t key = string_elem("apa");
  int value = 7;

  elem_t key2 = string_elem("delfin");
  int value2 = 42;

  elem_t key3 = string_elem("giraff");
  int value3 = 17;

  elem_t key4 = string_elem("sabeltandad tiger");

  //insert key-value pairs
  ioopm_hash_table_insert(ht, key, int_elem(value));
  ioopm_hash_table_insert(ht, key2, int_elem(value2));
  ioopm_hash_table_insert(ht, key3, int_elem(value3));

  //check if keys <= 3 are in ht check for key 4, which is not there
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key3));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key4));

  //destroy hashtable when done
  ioopm_hash_table_destroy(ht);
}

void test_ht_has_key4()
{
  //create new hashtable
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);

  // Make key-value pairs
  elem_t key = string_elem("apa");
  int value = 7;

  //insert key-value pair, immediately remove after
  ioopm_hash_table_insert(ht, key, int_elem(value));
  elem_t value_removed = ioopm_hash_table_remove(ht, key);
  
  //check removal succesfull, and that key is gone
  CU_ASSERT_EQUAL(value_removed.i, value);
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key));

  //destroy hashtable when done
  ioopm_hash_table_destroy(ht);
}

void test_ht_has_key5()
{
  //create new hashtable
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);

  // Make key-value pairs
  elem_t key = string_elem("apa");
  int value = 7;

  elem_t key2 = string_elem("delfin");
  int value2 = 42;

  elem_t key3 = string_elem("giraff");
  int value3 = 17;

  //insert key value pairs
  ioopm_hash_table_insert(ht, key, int_elem(value));
  ioopm_hash_table_insert(ht, key2, int_elem(value2));
  ioopm_hash_table_insert(ht, key3, int_elem(value3));

  //remove entry 2
  elem_t value_key2 = ioopm_hash_table_remove(ht, key2);

  //check that removal done, aswell as key2 gone, key and key3 still there
  CU_ASSERT_EQUAL(value_key2.i, value2);
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, key2));
  
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key3));

  //destroy hashtable when done
  ioopm_hash_table_destroy(ht);
}

void test1_ht_size()
{
  //create new hashtable
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);
  
  //checks that size returns 0 for empty ht
  int size_empty = 0;
  size_t size_ht = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(size_empty, size_ht);
  
  //destroy hashtable when done
  ioopm_hash_table_destroy(ht);
}

void test2_ht_size()
{
  //create new hashtable
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);
  
  // Make key-value pairs
  elem_t key = string_elem("apa");
  int value = 7;

  //insert key-value pair
  ioopm_hash_table_insert(ht, key, int_elem(value));
  
  //checks that size returns 1 for singelton ht
  int size1 = 1;
  size_t size_ht = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(size1, size_ht);
  
  //destroy hashtable when done
  ioopm_hash_table_destroy(ht);
}

void test3_ht_size()
{
  //create new hashtable
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);
  
  // Make key-value pairs
  elem_t key = string_elem("apa");
  int value = 7;

  elem_t key2 = string_elem("delfin");
  int value2 = 42;

  elem_t key3 = string_elem("giraff");
  int value3 = 17;

  //insert key value pairs
  ioopm_hash_table_insert(ht, key, int_elem(value));
  ioopm_hash_table_insert(ht, key2, int_elem(value2));
  ioopm_hash_table_insert(ht, key3, int_elem(value3));

  //checks that size returns 3 for ht with 3 entries
  int size3 = 3;
  size_t size_ht = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(size3, size_ht);
  
  //destroy hashtable when done
  ioopm_hash_table_destroy(ht);
}


void test4_ht_size()
{
  //create new hashtable
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);
  
  // Make key-value pairs
  elem_t key = string_elem ("apa");
  int value = 7;

  elem_t key2 = string_elem("delfin");
  int value2 = 42;

  elem_t key3 = string_elem("giraff");
  int value3 = 17;

  //insert key value pairs
  ioopm_hash_table_insert(ht, key, int_elem(value));
  ioopm_hash_table_insert(ht, key2, int_elem(value2));
  ioopm_hash_table_insert(ht, key3, int_elem(value3));

  //checks that size returns 3 for ht with 3 entries
  int size3 = 3;
  size_t size_ht = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(size3, size_ht);

  //checks that size returns 2 once a entry is removed from size 3 ht
  ioopm_hash_table_remove(ht, key);
  int size2 = 2;
  size_ht = ioopm_hash_table_size(ht);
  CU_ASSERT_EQUAL(size2, size_ht);
  
  //destroy hashtable when done
  ioopm_hash_table_destroy(ht);
}

void test_empty_ht()
{
  //create new hashtable
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);
  
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  
  // Make key-value pair
  elem_t key = string_elem("apa");
  int value = 7;
  
  //insert key value pairs
  ioopm_hash_table_insert(ht, key, int_elem(value));

  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  
  //destroy hashtable when done
  ioopm_hash_table_destroy(ht);
}

// 2.2 TESTS

void test_iterate_empty_ht()
{
  //create new hashtable and hashtable iterator
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  
  //check that iterator is at end of hashtable
  CU_ASSERT_TRUE(ioopm_hash_table_iterator_at_end(it));

  ioopm_hash_table_iterator_advance(it);
  
  //destroy iterator when done
  ioopm_hash_table_iterator_destroy(it);
  //destroy hashtable when done
  ioopm_hash_table_destroy(ht);
}

void test_iterate_single_ht()
{
  //create new hashtable and hashtable iterator
  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);
    
  // Make key-value pair
  elem_t key = string_elem("apa");
  int value = 7;
  
  //insert key value pairs
  ioopm_hash_table_insert(ht, key, int_elem(value));

  //make iterator once iteration is suppose to start
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);

  //Extract key and value of entry that it points to
  char *it_key = ioopm_hash_table_iterator_current_key(it).s;
  int it_value = ioopm_hash_table_iterator_current_value(it).i;
  
  //check that keys and values are the same
  CU_ASSERT_EQUAL(strcmp(it_key, key.s), 0);
  CU_ASSERT_EQUAL(it_value, value);

  //destroy iterator when done
  ioopm_hash_table_iterator_destroy(it);
  //destroy hashtable when done
  ioopm_hash_table_destroy(ht);
}

void test_iterator_several_entries()
{
  char *keys[3] = {"abc", "qwe", "asd"};
  int values[3] = {0, 1, 2};

  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);
  for (int i = 0; i < 3; i++)
  {
    ioopm_hash_table_insert(ht, string_elem(keys[i]), int_elem(values[i]));
  }

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  CU_ASSERT_EQUAL(iteration_count, 3);
  ioopm_hash_table_destroy(ht);
}

void test_keyvalue_visit_once()
{
  char *keys[3] = {"abc", "qwe", "asd"};
  int values[3] = {0, 1, 2};

  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);
  for (int i = 0; i != 3; ++i)
  {
    ioopm_hash_table_insert(ht, string_elem(keys[i]), int_elem(values[i]));
  }

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;

    char *it_key = ioopm_hash_table_iterator_current_key(it).s;

    if(strcmp(it_key, "abc") == 0)
    {
      CU_ASSERT_EQUAL(ioopm_hash_table_iterator_current_value(it).i, 0);
    }
    else if (strcmp(it_key, "qwe") == 0)
    {
      CU_ASSERT_EQUAL(ioopm_hash_table_iterator_current_value(it).i, 1);
    }
    else if (strcmp(it_key, "asd") == 0)
    {
      CU_ASSERT_EQUAL(ioopm_hash_table_iterator_current_value(it).i, 2);
    }

    ioopm_hash_table_iterator_advance(it);    
  }

  ioopm_hash_table_iterator_destroy(it);
  CU_ASSERT_EQUAL(iteration_count, 3);
  ioopm_hash_table_destroy(ht);
}

// TICKET 3, elem_t

void test_elem_t_values()
{
  char *keys[4] = {"apa", "björn", "chinchilla", "delfin"};
  elem_t values[4] = {true, ptr_elem(NULL), 7, string_elem("hej")};  

  ioopm_hash_table_t *ht = ioopm_hash_table_create(&string_knr_hash, &simple_knr_eq);
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, string_elem(keys[i]), values[i]);
  }

  elem_t result; 

  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, string_elem("apa"), &result));
  CU_ASSERT_TRUE(result.b);

  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, string_elem("björn"), &result));
  CU_ASSERT_PTR_NULL(result.p);

  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, string_elem("chinchilla"), &result));
  CU_ASSERT_EQUAL(result.i, 7);
  
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, string_elem("delfin"), &result));
  CU_ASSERT_TRUE(strcmp(result.s, "hej") == 0);

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  CU_ASSERT_EQUAL(iteration_count, 4);
  ioopm_hash_table_destroy(ht);
}

void test_elem_t_keys()
{
  int keys[4] = {0, 1, 2, 3};
  elem_t values[4] = {true, ptr_elem(NULL), 7, string_elem("hej")};  

  ioopm_hash_table_t *ht = ioopm_hash_table_create(&simple_int_hash, &simple_int_eq);
  for (int i = 0; i < 4; i++)
  {
    ioopm_hash_table_insert(ht, int_elem(keys[i]), values[i]);
  }

  elem_t result; 

  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, int_elem(0), &result));
  CU_ASSERT_TRUE(result.b);

  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, int_elem(1), &result));
  CU_ASSERT_PTR_NULL(result.p);

  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, int_elem(2), &result));
  CU_ASSERT_EQUAL(result.i, 7);
  
  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, int_elem(3), &result));
  CU_ASSERT_TRUE(strcmp(result.s, "hej") == 0);

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  CU_ASSERT_EQUAL(iteration_count, 4);
  ioopm_hash_table_destroy(ht);
}

void test_bool_keys()
{
  bool keys[2] = {true, false};
  elem_t values[2] = {string_elem("hund"), int_elem(7)};  

  ioopm_hash_table_t *ht = ioopm_hash_table_create(&simple_bool_hash, &simple_bool_eq);
  for (int i = 0; i < 2; i++)
  {
    ioopm_hash_table_insert(ht, bool_elem(keys[i]), values[i]);
  }

  elem_t result; 

  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, bool_elem(true), &result));
  CU_ASSERT_TRUE(strcmp(result.s, "hund") == 0);

  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, bool_elem(false), &result));
  CU_ASSERT_EQUAL(result.i, 7);

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  CU_ASSERT_EQUAL(iteration_count, 2);
  ioopm_hash_table_destroy(ht);
}

void test_ptr_key()
{
  int key1; 
  elem_t ptr1 = ptr_elem(&key1);
  int key2; 
  elem_t ptr2 = ptr_elem(&key2);
  
  elem_t keys[2] = {ptr1, ptr2};
  elem_t values[2] = {string_elem("hund"), int_elem(7)};  

  ioopm_hash_table_t *ht = ioopm_hash_table_create(&simple_bool_hash, &simple_bool_eq);
  for (int i = 0; i < 2; i++)
  {
    ioopm_hash_table_insert(ht, keys[i], values[i]);
  }

  elem_t result; 

  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, ptr1, &result));
  CU_ASSERT_TRUE(strcmp(result.s, "hund") == 0);

  CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, ptr2, &result));
  CU_ASSERT_EQUAL(result.i, 7);

  int iteration_count = 0;

  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  while (!ioopm_hash_table_iterator_at_end(it))
  {
    iteration_count++;
    ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
  CU_ASSERT_EQUAL(iteration_count, 2);
  ioopm_hash_table_destroy(ht);
}

// Main function
int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite ticket_1_suite = CU_add_suite("Ticket 1 test suite", init_suite, clean_suite);
  if (ticket_1_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  CU_pSuite ticket_2_suite = CU_add_suite("Ticket 2 test suite", init_suite, clean_suite);
  if (ticket_2_suite == NULL) {
      // If the test suite could not be added, tear down CUnit and exit
      CU_cleanup_registry();
      return CU_get_error();
  }

  CU_pSuite ticket_3_suite = CU_add_suite("Ticket 3 test suite", init_suite, clean_suite);
  if (ticket_3_suite == NULL) {
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
    (CU_add_test(ticket_1_suite, "Create result non-empty", test_create_destroy) == NULL) ||
    (CU_add_test(ticket_1_suite, "Test insert once works", test_insert_once) == NULL) ||
    (CU_add_test(ticket_1_suite, "Test insert twice works", test_insert_twice) == NULL) ||
    (CU_add_test(ticket_1_suite, "Test update value, old key", test_update_val) == NULL) ||
    (CU_add_test(ticket_1_suite, "Test hash table remove an entry", test_hash_table_remove) == NULL) ||
    (CU_add_test(ticket_2_suite, "Test1 hash table has key", test_ht_has_key1) == NULL) ||
    (CU_add_test(ticket_2_suite, "Test2 hash table has key", test_ht_has_key2) == NULL) ||
    (CU_add_test(ticket_2_suite, "Test3 hash table has key", test_ht_has_key3) == NULL) ||
    (CU_add_test(ticket_2_suite, "Test4 hash table has key", test_ht_has_key4) == NULL) ||
    (CU_add_test(ticket_2_suite, "Test5 hash table has key", test_ht_has_key5) == NULL) ||
    (CU_add_test(ticket_2_suite, "Test1 hash table size", test1_ht_size) == NULL) ||
    (CU_add_test(ticket_2_suite, "Test2 hash table size", test2_ht_size) == NULL) ||
    (CU_add_test(ticket_2_suite, "Test3 hash table size", test3_ht_size) == NULL) ||
    (CU_add_test(ticket_2_suite, "Test4 hash table size", test4_ht_size) == NULL) ||
    (CU_add_test(ticket_2_suite, "Test hash table empty", test_empty_ht) == NULL) ||
    (CU_add_test(ticket_2_suite, "Test it empty", test_iterate_empty_ht) == NULL) ||
    (CU_add_test(ticket_2_suite, "Test it single", test_iterate_single_ht) == NULL) ||
    (CU_add_test(ticket_2_suite, "Test it several entries", test_iterator_several_entries) == NULL) ||
    (CU_add_test(ticket_2_suite, "Test it keyvalue visited once", test_keyvalue_visit_once) == NULL) ||
    (CU_add_test(ticket_3_suite, "Tests elem_t values", test_elem_t_values) == NULL) ||
    (CU_add_test(ticket_3_suite, "Tests int keys", test_elem_t_keys) == NULL) ||
    (CU_add_test(ticket_3_suite, "Tests bool keys", test_bool_keys) == NULL) ||
    (CU_add_test(ticket_3_suite, "Tests ptr keys", test_bool_keys) == NULL) ||
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
