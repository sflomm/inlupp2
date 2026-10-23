#include "../generic_types/hash_table.h"
#include "../generic_types/common.h"
#include "../generic_types/hash_table_struct.h"
#include "../generic_types/hash_table_iterator.h"
#include "../generic_types/linked_list_struct.h"
#include "../generic_types/linked_list.h"
#include "../generic_types/list_iterator.h"
#include "../generic_types/hash_table_iterator.h"
#include "webstore_types.h"
#include "webstore_backend.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

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

warehouse_t *warehouse_create()
{
    //merch table
    ioopm_hash_table_t *merch_ht = ioopm_hash_table_create(string_knr_hash, simple_knr_eq);
    //table of locations
    ioopm_hash_table_t *location_ht = ioopm_hash_table_create(string_knr_hash, simple_knr_eq);
    //struct of carts
    carts_t *carts = calloc(1, sizeof(carts_t));
    //table of shopping carts
    ioopm_list_t *carts_list = ioopm_list_create();
    

    warehouse_t *warehouse = calloc(1, sizeof(warehouse_t));
    warehouse->merch_ht = merch_ht;
    warehouse->location_ht = location_ht;
    warehouse->carts = carts;
    warehouse->carts->carts_list = carts_list;
    warehouse->carts->count = 0;
    
    return warehouse;
}

void warehouse_destroy_all_merch(warehouse_t *wh) {
  
  ioopm_hash_table_iterator_t *iter = ioopm_hash_table_iterator_create(wh->merch_ht);

  while (!ioopm_hash_table_iterator_at_end(iter))
  {
      elem_t value = ioopm_hash_table_iterator_current_value(iter);
      merch_t *merch = value.p;

      // Free locations if the merchandise owns this list
      if (merch->locs != NULL)
      {
          ioopm_list_destroy(merch->locs);
      }

      free(merch);

      ioopm_hash_table_iterator_advance(iter);
  }

  ioopm_hash_table_iterator_destroy(iter);
}

void warehouse_destroy(warehouse_t *wh) {
  warehouse_destroy_all_merch(wh);
  ioopm_hash_table_destroy(wh->merch_ht);
  ioopm_hash_table_destroy(wh->location_ht);
  ioopm_list_destroy(wh->carts->carts_list);
  free(wh->carts);

  free(wh);
}

// FIXME: asserts? får man skicka in ett tomt varuhus?
merch_t *warehouse_find_merch(warehouse_t *wh, char *key)
{
  ioopm_hash_table_t *ht = wh->merch_ht;
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  merch_t *current_merch;

  while (!ioopm_hash_table_iterator_at_end(it))
  {
    char *current_key = ioopm_hash_table_iterator_current_key(it).s;
    if (strcmp(current_key, key) == 0)
    {
      current_merch = it->current_entry->value.p;
      return current_merch; 
    }
    else 
    {
      ioopm_hash_table_iterator_advance(it);
    }
  }
  return NULL;
}

// static bool warehouse_merch_exists(warehouse_t *wh, char *key)
// {
//   return ioopm_hash_table_has_key(wh->merch_ht, string_elem(key));
// }

void warehouse_add_merch(warehouse_t *wh, char *name, char *desc, size_t price)
{        
    merch_t *merch = calloc(1, sizeof(merch_t));
    merch->name = name;
    merch->desc = desc;
    merch->price = price;
    merch->locs = NULL;
  
    ioopm_hash_table_insert(wh->merch_ht, string_elem(name), ptr_elem(merch));
}

// static shelf_t warehouse_find_shelf(ioopm_list_t *list, char *shelf)
// {
//   ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);
 
  
// }

void warehouse_replenish_stock(warehouse_t *wh, char *shelf, merch_t *merch, size_t add_quant)
{
  if (!ioopm_hash_table_has_key(wh->location_ht, string_elem(shelf)))
  {
    ioopm_hash_table_insert(wh->location_ht, string_elem(shelf), ptr_elem(merch));
    shelf_t *new_shelf = calloc(1, sizeof(shelf_t)); // FIXME: kom ihåg att frigöra pekaren i destroy
    new_shelf->shelf = shelf;
    new_shelf->quant = add_quant;
    ioopm_list_insert(merch->locs, 0, ptr_elem(new_shelf));
  }
  else 
  {
    // shelf_t *shelf = warehouse_find_shelf(merch->locs, merch->locs->shelf);
  }
}


// TODO, inte klar
// void warehouse_list_merch(warehouse_t *wh)
// {
//   (void) wh;
  // ioopm_hash_table_t *merch_ht = wh->merch_ht;
  // ioopm_hash_table_iterator_t *merch_it = ioopm_hash_table_iterator_create(merch_ht);
  // elem_t current_key = ioopm_hash_table_iterator_current_key(merch_it);
  // int n = 0; 

  // FIXME: ui print 20 more, action code "L" -> n -> return to menu
  // FIXME: alphabetically
//   while (!ioopm_hash_table_iterator_at_end(merch_it) && n <= 20)
//   {
//     printf("%d. %s\n", n, current_key.s);
//     ioopm_hash_table_iterator_advance(merch_it);
//     ioopm_hash_table_iterator_current_key(merch_it);
//   }
//   (void) wh;
// }

void warehouse_remove_merch(warehouse_t *wh, char *key)
{
  // TODO: måste frigöra alla pekare
  (void) wh;
  (void) key;
}

void warehouse_edit_merch(warehouse_t *wh, char *key)
{
  // TODO: Stub
  (void) wh;
  (void) key;
}

void warehouse_show_stock(warehouse_t *wh, char *key)
{
  // TODO: Stub
  (void) wh;
  (void) key;
}
