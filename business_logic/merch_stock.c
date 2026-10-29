#include "../generic_types/hash_table.h"
#include "../generic_types/hash_table_struct.h"
#include "../generic_types/hash_table_iterator.h"
#include "../generic_types/linked_list_struct.h"
#include "../generic_types/linked_list.h"
#include "../generic_types/list_iterator.h"
#include "../generic_types/common.h"
#include "webstore_types.h"
#include "webstore_backend.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define PAGE_SIZE 20

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

// free allocated memory for locations-list with struct shelf_t
static void warehouse_destroy_locations(ioopm_list_t *list)
{
    link_t *current_link = list->first;
    link_t *current_next;
    
    while (current_link != NULL)
    {
        current_next = current_link->next;
        free(current_link->element.p); 
        free(current_link);
        current_link = current_next;    
    }
    
    free(list);
}

// free allocated memory for merch struct
static void warehouse_destroy_all_merch(warehouse_t *wh) {
  
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(wh->merch_ht);

  while (!ioopm_hash_table_iterator_at_end(it))
  {
      elem_t value = ioopm_hash_table_iterator_current_value(it);
      merch_t *merch = value.p;

      // Free locations if the merchandise owns this list
      if (merch->locs != NULL)
      {
          warehouse_destroy_locations(merch->locs);
      }

      free(merch);

      ioopm_hash_table_iterator_advance(it);
  }

  ioopm_hash_table_iterator_destroy(it);
}

static void warehouse_destroy_one_merch(merch_t *merch)
{
  if (merch == NULL)
  {
    return;
  }

 if (merch->locs != NULL)
 {
  warehouse_destroy_locations(merch->locs);
 }

  free(merch);
}

void warehouse_destroy(warehouse_t *wh) {
  warehouse_destroy_all_merch(wh);
  ioopm_hash_table_destroy(wh->merch_ht);
  ioopm_hash_table_destroy(wh->location_ht);
  ioopm_list_destroy(wh->carts->carts_list);
  free(wh->carts);

  free(wh);
}

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
      ioopm_hash_table_iterator_destroy(it);
      return current_merch; 
    }
    else 
    {
      ioopm_hash_table_iterator_advance(it);
    }
  }
  ioopm_hash_table_iterator_destroy(it);
  return NULL;
}

void warehouse_add_merch(warehouse_t *wh, char *name, char *desc, size_t price)
{        
    merch_t *merch = calloc(1, sizeof(merch_t));
    merch->name = name;
    merch->desc = desc;
    merch->price = price;
    merch->locs = ioopm_list_create();
  
    ioopm_hash_table_insert(wh->merch_ht, string_elem(name), ptr_elem(merch));
}

// TODO: printa 20 i taget och välja om man vill fortsätta
// alpabetisk ordning hade varit najs att få till
void warehouse_list_merch(warehouse_t *wh)
{
  ioopm_hash_table_t *merch_ht = wh->merch_ht;
  ioopm_hash_table_iterator_t *merch_it = ioopm_hash_table_iterator_create(merch_ht);
  int amount_of_merch = 0;

  // prints 20 merch
  while (!ioopm_hash_table_iterator_at_end(merch_it) && amount_of_merch < 20)
  {
    char *current_key = ioopm_hash_table_iterator_current_key(merch_it).s;
    printf("%d. %s\n", amount_of_merch + 1, current_key);
    ioopm_hash_table_iterator_advance(merch_it);
    amount_of_merch++;
  }

  // UI: would you like to print 20 more? 
  // while answer != "n/N" -> kör loop och printa 20 varje gång tills slutet av hash tablets slut.

}

bool warehouse_remove_merch(warehouse_t *wh, char *key)
{
  merch_t *merch = warehouse_find_merch(wh, key);
  if (merch == NULL)
  {
    return false;
  }
  warehouse_destroy_one_merch(merch);
  ioopm_hash_table_remove(wh->merch_ht, string_elem(key));
  return true;
}

void warehouse_edit_merch(warehouse_t *wh, char *key, char *new_name, char* new_desc, size_t new_price)
{
  
  merch_t *merch = warehouse_find_merch(wh, key);
  if (merch == NULL)
  {
    // puts("Merch not found.\n");
    return;
  }

  if (strcmp(key, new_name) != 0)
  {
    if (warehouse_find_merch(wh, new_name) != NULL)
    {
      // puts("Merch with new suggested name already exists.\n");
      return;
    }

    merch_t *new_merch = ioopm_hash_table_remove(wh->merch_ht, string_elem(key)).p;
    new_merch->name = new_name;
    new_merch->desc = new_desc;
    new_merch->price = new_price;
    ioopm_hash_table_insert(wh->merch_ht, string_elem(new_name), ptr_elem(new_merch));
  }
  else
  {
    merch->desc = new_desc;
    merch->price = new_price;
  }
}

// TODO: alphabetical order 
void warehouse_show_stock(warehouse_t *wh, char *key)
{
  merch_t *merch = warehouse_find_merch(wh, key);
  ioopm_list_iterator_t *it = ioopm_list_iterator_create(merch->locs);

  while (!ioopm_list_iterator_at_end(it))
  {
    link_t *current_link = ioopm_list_iterator_current(it).p;
    shelf_t *current_shelf = current_link->element.p;
    size_t quant = current_shelf->quant;
    char *shelf = current_shelf->shelf;
    printf("Shelf: %s. Stock: %d\n", shelf, quant);
    ioopm_list_iterator_advance(it);
  }

  ioopm_list_iterator_destroy(it);
}

static shelf_t *warehouse_find_shelf(ioopm_list_t *list, char *shelf)
{
  shelf_t *result = NULL; 
  if (list == NULL)
  {
    return result;
  }

  ioopm_list_iterator_t *it = ioopm_list_iterator_create(list);
  while (!ioopm_list_iterator_at_end(it))
  {
    shelf_t *current_shelf = ioopm_list_iterator_current(it).p;
    char *shelf_name = current_shelf->shelf;

    if (strcmp(shelf_name, shelf) == 0)
    {
      result = current_shelf;
      break;
    }
    ioopm_list_iterator_advance(it);
  }

  ioopm_list_iterator_destroy(it);
  return result;
}

void warehouse_replenish_stock(warehouse_t *wh, char *shelf, merch_t *merch, size_t add_quant)
{
  shelf_t *shelf_to_replenish = warehouse_find_shelf(merch->locs, shelf);

  if (shelf_to_replenish == NULL) // shelf finns inte
  {
    shelf_t *new_shelf = calloc(1, sizeof(shelf_t)); // FIXME: kom ihåg att frigöra shelfen, kanske redan görs i destroy?
    new_shelf->shelf = shelf;
    new_shelf->quant = add_quant;
    ioopm_list_insert(merch->locs, 0, ptr_elem(new_shelf));
    ioopm_hash_table_insert(wh->location_ht, string_elem(new_shelf->shelf), ptr_elem(merch));
  }
  else // shelf finns
  {
    shelf_to_replenish->quant += add_quant;
  }
  merch->stock += add_quant;
}