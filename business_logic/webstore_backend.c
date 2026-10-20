#include "../generic_types/hash_table.h"
#include "../generic_types/common.h"
#include "../generic_types/webstore_types.h"
#include "../generic_types/webstore_types.h"
#include "../generic_types/hash_table_struct.h"
#include "../generic_types/hash_table_iterator.h"
#include "../generic_types/linked_list_struct.h"
#include "../generic_types/linked_list.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    shopping_cart_t *carts = calloc(1, sizeof(shopping_cart_t));
        //table of shopping carts
    ioopm_list_t *cart_list = ioopm_list_create();

    warehouse_t *warehouse = calloc(1, sizeof(warehouse_t));
    warehouse->merch_ht = merch_ht;
    warehouse->location_ht = location_ht;
    warehouse->carts = carts;
    warehouse->carts->cart_list = cart_list;
    warehouse->carts->id = 0;
    
    return warehouse;
}
  void warehouse_destroy_merch(warehouse_t *wh) {
ioopm_hash_table_iterator_t *iter =
    ioopm_hash_table_iterator_create(wh->merch_ht);

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
  warehouse_destroy_merch(wh);
  ioopm_hash_table_destroy(wh->merch_ht);
  ioopm_hash_table_destroy(wh->location_ht);
  ioopm_list_destroy(wh->carts->cart_list);
  free(wh->carts);

  free(wh);
}

// FIXME: asserts? får man skicka in ett tomt varuhus?
merch_t *find_merch(warehouse_t *wh, char *key)
{
  ioopm_hash_table_t *ht = wh->merch_ht;
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(ht);
  merch_t *current_merch;

  while (!ioopm_hash_table_iterator_at_end(it))
  {
    if (ioopm_hash_table_iterator_current_key == key)
    {
      current_merch = it->current_entry->value.p;
      return current_merch; 
    }
    else 
    {
      ioopm_list_iterator_advance(it);
    }
  }
  return NULL;
}

void warehouse_add_merch(warehouse_t *wh, char *name, char *desc, int price)
{
    // FIXME: check if merch exists
    merch_t *merch = calloc(1, sizeof(merch_t));
    merch->name = name;
    merch->desc = desc;
    merch->price = price;
    merch->locs = NULL;
  
    ioopm_hash_table_insert(wh->merch_ht, string_elem(name), ptr_elem(merch));

}

void warehouse_list_merch(warehouse_t *wh)
{
  ioopm_hash_table_t *merch_ht = wh->merch_ht;
  ioopm_hash_table_iterator_t *merch_it = ioopm_hash_table_iterator_create(merch_ht);
  elem_t current_key = ioopm_hash_table_iterator_current_key(merch_it);
  size_t c = 0; // counter

  // FIXME: ui print 20 more, action code "L" -> n -> return to menu
  // FIXME: alphabetically
  while (!ioopm_hash_table_iterator_at_end(merch_it) && c <= 20)
  {
    printf("%d. %s\n", c, current_key);
    ioopm_hash_table_iterator_advance(merch_it);
    ioopm_hash_table_iterator_current_key(merch_it);
    c++; // increase counter 
  }
  (void) wh;
}

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

size_t warehouse_replenish_stock(warehouse_t *wh, char *key, int quant)
{
  // TODO: Stub  
  (void) wh;
  (void) key;
  (void) quant;
  return 0;
}

size_t warehouse_create_cart(warehouse_t *wh)
{
    shopping_cart_t *cart = calloc(1, sizeof(*cart));

    wh->carts->count++;

    cart->items = ioopm_hash_table_create(string_knr_hash, simple_knr_eq);

    ioopm_list_insert(wh->carts->cart_list, 0, ptr_elem(cart));

    return cart->id;
}


void warehouse_remove_cart(warehouse_t *wh, char *key)
{
  // TODO: Stub
  (void) wh;
  (void) key;
}

void warehouse_add_to_cart(ioopm_hash_table_t *cart_ht, char *cart, char *merch, int quant)
{
  ioopm_hash_table_t *cart = ioopm_hash_table_create(string_knr_hash, simple_knr_eq);
    ioopm_hash_table_insert
}

void warehouse_remove_from_cart(ioopm_hash_table_t *cart_ht, char *cart, char *merch, int quant)
{
  // TODO: Stub
  (void) cart_ht;
  (void) cart;
  (void) merch;
  (void) quant;
}

size_t warehouse_calculate_cost(ioopm_hash_table_t *cart_ht, char *cart)
{
  // TODO: Stub
  (void) cart_ht;
  (void) cart;
}

void warehouse_checkout(warehouse_t *wh, char *cart)
{
  // TODO: Stub
  (void) wh;
  (void) cart;
}

