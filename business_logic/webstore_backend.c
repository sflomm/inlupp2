#include "hash_table.h"
#include "common.h"
#include "webstore_types.h"
#include "webstore_types.h"
#include "hash_table_struct.h"
#include <stdio.h>

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

    warehouse_t *warehouse = calloc(1, sizeof(warehouse_t));
    warehouse->merch_ht = merch_ht;
    warehouse->location_ht = location_ht;

    return warehouse;
}

void warehouse_destroy(ioopm_hash_table_t *ht1, ioopm_hash_table_t *ht2)
{
    ioopm_hash_table_destroy(ht1);
    ioopm_hash_table_destroy(ht2);
}

void warehouse_add_merch(char *name, char *desc, int price, warehouse_t *wh)
{
    // FIXME: check if merch exists
    merch_t *merch = calloc(1, sizeof(merch_t));
    merch->name = name;
    merch->desc = desc;
    merch->price = price;
    merch->locs = NULL;
  
    ioopm_hash_table_insert(wh->merch_ht, string_elem(name), ptr_elem(merch));

}

// list all items in store, alphabetically ordered
// print 20 at a time, ask user if they want to continue listing 20 more
// action code "L", "n" return to main menu
void warehouse_list_merch(warehouse_t *wh)
{
  // TODO: Stub
}

void warehouse_remove_merch(warehouse_t *wh, char *key)
{
  // TODO: Stub
}

void warehouse_edit_merch()
{
  // TODO: Stub
}

void warehouse_show_stock()
{
  // TODO: Stub
}

void warehouse_replenish_stock()
{
  // TODO: Stub  
}

void warehouse_create_cart()
{
  // TODO: Stub
}

void warehouse_remove_cart()
{
  // TODO: Stub
}

void warehouse_add_to_cart()
{
  // TODO: Stub
}

void warehouse_remove_from_cart()
{
  // TODO: Stub
}

void warehouse_calculate_cost()
{
  // TODO: Stub
}

void warehouse_checkout()
{
  // TODO: Stub
}