#include <CUnit/Basic.h>
#include <string.h>
#include "linked_list_struct.h"
#include "linked_list.h"
#include "list_iterator.h"



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

// Write test functions here

// Checks that result from create is not NULL
void test_create_destroy()
{
  //create new list
  ioopm_list_t *list = ioopm_list_create();
  
  //list pointer exists and list is empty
  CU_ASSERT_PTR_NOT_NULL(list);
  CU_ASSERT(ioopm_list_is_empty(list));

  //destroy list
  ioopm_list_destroy(list);
}

void test_prepend_append()
{
  //create new list
  ioopm_list_t *list = ioopm_list_create(); 

  // make list(3,7)
  ioopm_list_append(list, int_elem(7));
  ioopm_list_prepend(list, int_elem(3));
  
  //save head, last and size
  elem_t first = ioopm_list_head(list);  
  elem_t last = ioopm_list_last(list);
  size_t size = ioopm_list_size(list); 

  CU_ASSERT_EQUAL(first.i, 3);
  CU_ASSERT_EQUAL(last.i, 7); 
  CU_ASSERT_EQUAL(size, 2); // two elements

  // destroy list 
  ioopm_list_destroy(list);
}

void test_get_correct()
{
  //create new list
  ioopm_list_t *list = ioopm_list_create();
  
  ioopm_list_prepend(list, int_elem(3));
  ioopm_list_append(list, int_elem(4));
  ioopm_list_prepend(list, int_elem(7));
  ioopm_list_append(list, int_elem(8)); // list(7,3,4,8)

  elem_t first = ioopm_list_get(list, 0); // 7
  elem_t second = ioopm_list_get(list, 1); // 3
  elem_t third = ioopm_list_get(list, 2); // 4
  elem_t fourth = ioopm_list_get(list, 3); // 8
  
  // check if correct placement 
  CU_ASSERT_EQUAL(first.i, 7);
  CU_ASSERT_EQUAL(second.i, 3);
  CU_ASSERT_EQUAL(third.i, 4);
  CU_ASSERT_EQUAL(fourth.i, 8);
  
  // destroy list
  ioopm_list_destroy(list);
}

void test_insert_list()
{
  //create new list
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_insert(list, 0, int_elem(1));
  ioopm_list_insert(list, 1, int_elem(2));
  ioopm_list_insert(list, 2, int_elem(3)); // list(1, 2, 3)

  ioopm_list_insert(list, 2, int_elem(7)); // list(1, 2, 7, 3)
  elem_t inserted = ioopm_list_get(list, 2); // index 2 = 7
  CU_ASSERT_EQUAL(inserted.i, 7);

  ioopm_list_insert(list, 0, int_elem(53)); // list(53, 1, 2, 7, 3)
  elem_t first = ioopm_list_head(list); // first element = 53
  CU_ASSERT_EQUAL(first.i, 53);

  ioopm_list_insert(list, 5, int_elem(42)); // list(53, 1, 2, 7, 3, 42)
  elem_t last = ioopm_list_last(list); // last element = 42
  CU_ASSERT_EQUAL(last.i, 42);

  // destroy list
  ioopm_list_destroy(list);
}

void test_remove()
{
  //create new list
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_insert(list, 0, int_elem(1));
  ioopm_list_insert(list, 1, int_elem(2));
  ioopm_list_insert(list, 2, int_elem(3)); 
  ioopm_list_append(list, int_elem(4));
  ioopm_list_append(list, int_elem(5));
  ioopm_list_append(list, int_elem(6)); // list(1,2,3,4,5,6)
  
  CU_ASSERT_EQUAL(ioopm_list_size(list), 6); 
  elem_t removed_first = ioopm_list_remove(list, 0); // list(2,3,4,5,6)
  CU_ASSERT_EQUAL(removed_first.i, 1);
  CU_ASSERT_EQUAL(ioopm_list_size(list), 5); 
  CU_ASSERT_EQUAL(ioopm_list_head(list).i, 2); 

  elem_t removed_last = ioopm_list_remove(list, 4); // list(2,3,4,5)
  CU_ASSERT_EQUAL(removed_last.i, 6); 
  CU_ASSERT_EQUAL(ioopm_list_size(list), 4); 
  CU_ASSERT_EQUAL(ioopm_list_last(list).i, 5); 
  
  elem_t removed_third = ioopm_list_remove(list, 2); // list(2,3,5)
  CU_ASSERT_EQUAL(removed_third.i, 4); 
  CU_ASSERT_EQUAL(ioopm_list_size(list), 3); 
  CU_ASSERT_EQUAL(ioopm_list_get(list, 2).i, 5); 

  // destroy list
  ioopm_list_destroy(list);
}

void test_iter_create_destroy()
{
  //create new list
  ioopm_list_t *list = ioopm_list_create();
  //create new list iterator
  ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
  
  //iter poelem_ter, and fields are correct
  CU_ASSERT_PTR_NOT_NULL(iter);
  CU_ASSERT_EQUAL(iter->current_index, 0); //"start" is at idx 0 (even for empty list)
  CU_ASSERT_PTR_NULL(iter->current_link); //empty list, current link NULL
  CU_ASSERT_PTR_EQUAL(iter->list, list); //list and iter->list same
  
  //destroy iterator and list
  ioopm_list_iterator_destroy(iter);
  ioopm_list_destroy(list);
}

void test_iter_at_end()
{
  //create new list
  ioopm_list_t *list = ioopm_list_create();
  //create new list iterator
  ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);

  //iter is at end if list is empty
  CU_ASSERT(ioopm_list_iterator_at_end(iter));

  //destroy iterator and list
  ioopm_list_iterator_destroy(iter);
  ioopm_list_destroy(list);
}

void test_iter_current()
{
  //create new list
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_append(list, int_elem(0));
  ioopm_list_append(list, int_elem(1));
  ioopm_list_append(list, int_elem(2)); // list 0, 1, 2

  //create new list iterator
  ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);

  //check correct first
  elem_t first = ioopm_list_iterator_current(iter);
  CU_ASSERT_EQUAL(first.i, 0);
  
  ioopm_list_iterator_advance(iter); //iter poelem_ts to 1
  CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter).i, 1);
  
  ioopm_list_iterator_advance(iter); //iter poelem_ts to 2
  CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter).i, 2);

  //destroy iterator and list
  ioopm_list_iterator_destroy(iter);
  ioopm_list_destroy(list);
}

void test_iter_remove()
{
  //create new list
  ioopm_list_t *list = ioopm_list_create();

  ioopm_list_append(list, int_elem(0));
  ioopm_list_append(list, int_elem(1));
  ioopm_list_append(list, int_elem(2));
  ioopm_list_append(list, int_elem(3)); //list 0, 1, 2, 3

  //create new list iterator
  ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
  
  ioopm_list_iterator_advance(iter); //iter poelem_ts to 1
  CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter).i, 1);
  
  //remove elem that iter points to, check correct elem removed
  elem_t removed = ioopm_list_iterator_remove(iter);
  CU_ASSERT_EQUAL(removed.i, 1);
  //check new current correct
  CU_ASSERT_EQUAL(ioopm_list_iterator_current(iter).i, 2);

  //destroy iterator and list
  ioopm_list_iterator_destroy(iter);
  ioopm_list_destroy(list);
}

void test_iter_insert()
{
  //create new list
  ioopm_list_t *list = ioopm_list_create();
  
  ioopm_list_append(list, int_elem(0));
  ioopm_list_append(list, int_elem(1));
  ioopm_list_append(list, int_elem(2));// list 0, 1, 2
  
  //create new list iterator
  ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
  
  ioopm_list_iterator_insert(iter, int_elem(7)); //list 7, 0, 1, 2
  CU_ASSERT_EQUAL(ioopm_list_head(list).i, 7);

  ioopm_list_iterator_advance(iter); //iter poelem_ts at 1
  ioopm_list_iterator_insert(iter, int_elem(10)); // list 7, 0, 10, 1, 2
  CU_ASSERT_EQUAL(ioopm_list_get(list, 2).i, 10);

  //destroy iterator and list
  ioopm_list_iterator_destroy(iter);
  ioopm_list_destroy(list);
}

void test_all_types()
{
    //create new list
  ioopm_list_t *list = ioopm_list_create();
  
  ioopm_list_append(list, int_elem(0));
  ioopm_list_append(list, bool_elem(true));
  ioopm_list_append(list, ptr_elem(NULL));// list (0, true, NULL)
  
  //create new list iterator
  ioopm_list_iterator_t *iter = ioopm_list_iterator_create(list);
  
  ioopm_list_iterator_insert(iter, string_elem("hello, world!")); //list ("hello,world!", 0, true, NULL)
  CU_ASSERT_TRUE(strcmp(ioopm_list_head(list).s, "hello, world!") == 0);

  ioopm_list_iterator_advance(iter); //iter points at true
  ioopm_list_iterator_insert(iter, int_elem(10)); // list ("hello,world!", 0, 10, true, NULL)

  CU_ASSERT_TRUE(strcmp(ioopm_list_get(list, 0).s, "hello,world!") == 0);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 1).i, 0);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 2).i, 10);
  CU_ASSERT_EQUAL(ioopm_list_get(list, 3).b, true);
  CU_ASSERT_PTR_NULL(ioopm_list_get(list, 4).p);

  //destroy iterator and list
  ioopm_list_iterator_destroy(iter);
  ioopm_list_destroy(list);
}

// Main function
int main() {
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
  {
    return CU_get_error();
  }
  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
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
    (CU_add_test(ticket_3_suite, "Test create and destroy", test_create_destroy) == NULL) ||
    (CU_add_test(ticket_3_suite, "Test prepend, append, head and last", test_prepend_append) == NULL) ||
    (CU_add_test(ticket_3_suite, "Test get correct element", test_get_correct) == NULL) ||
    (CU_add_test(ticket_3_suite, "Test insert list", test_insert_list) == NULL) ||
    (CU_add_test(ticket_3_suite, "Test remove element", test_remove) == NULL) ||
    (CU_add_test(ticket_3_suite, "Test iter create and destroy", test_iter_create_destroy) == NULL) ||
    (CU_add_test(ticket_3_suite, "Test iter at end", test_iter_at_end) == NULL) ||
    (CU_add_test(ticket_3_suite, "Test iter current", test_iter_current) == NULL) ||
    (CU_add_test(ticket_3_suite, "Test iter remove", test_iter_remove) == NULL) ||
    (CU_add_test(ticket_3_suite, "Test iter insert", test_iter_insert) == NULL) ||
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
