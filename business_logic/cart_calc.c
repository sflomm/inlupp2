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

shopping_cart_t warehouse_create_cart(warehouse_t *wh)
{
  wh->carts->count++;  

  shopping_cart_t *cart = calloc(1, sizeof(*cart));
    cart->id = wh->carts->count;
    cart->items = ioopm_hash_table_create(string_knr_hash, simple_knr_eq);

    ioopm_list_insert(wh->carts->carts_list, 0, ptr_elem(cart));

    return *cart;
}


void warehouse_remove_cart(warehouse_t *wh, char *key)
{
  // TODO: Stub
  (void) wh;
  (void) key;
}

static bool quant_assert(size_t quant) {
  if (quant == 0) {
    return false;
  }
  return true;
}

static shopping_cart_t *warehouse_find_shopping_cart(warehouse_t *wh, char *cart_id) {

    ioopm_list_iterator_t *it =
        ioopm_list_iterator_create(wh->carts->carts_list);

    while (!ioopm_list_iterator_at_end(it))
    {
        elem_t value = ioopm_list_iterator_current(it);
        shopping_cart_t *value_cart;

        if (value_cart->id == cart_id)
        return value_cart;
      }
      return NULL;
}

bool warehouse_add_to_cart(warehouse_t *wh, size_t cart_id,
                            char *merch, size_t quant)
{
//quant cant be less then or equal to zero
  assert(quant_assert(quant));
 //Check if merch exists
   assert(warehouse_merch_exists(wh, merch));

  shopping_cart_t *cart = warehouse_find_shopping_cart(wh, cart_id);
   ioopm_list_iterator_t *it;
       ioopm_list_iterator_create(wh->carts->carts_list);

    while (!ioopm_list_iterator_at_end(it))
    {
       elem_t value = ioopm_list_iterator_current(it);
        shopping_cart_t *value_cart = value.p;

            ioopm_list_iterator_destroy(it);
            return true;
            
         }

        ioopm_list_iterator_advance(it);
    
    //cart doesnt exist
    ioopm_list_iterator_destroy(it);
    return false;
}

bool warehouse_remove_from_cart(warehouse_t *wh, size_t cart_id, char *merch, size_t quant)
{
    //quant cant be zero
    assert(quant_assert(quant));
    //merch must exist in warehouse
    assert(warehouse_merch_exists(wh, merch));
    shopping_cart_t cart = warehouse_find_shopping_cart(wh, cart_id);
    merch_t *merch_type = wh->merch_ht->buckets->value;
            //no need to check if items already has key beacuse insert function handles that
            if (quant <= merch_type->stock) {
                ioopm_hash_table_insert(value_cart->items, merch, quant);
                ioopm_list_iterator_destroy(it);
                return true;
            }
            //quant is bigger than stock
            else {
                ioopm_list_destroy(it);
                return false;
            }
}

size_t warehouse_calculate_cost(warehouse_t *wh, char *cart_id)
{
  size_t price_empty_cart = 0;
  ioopm_hash_table_t *ht = wh->carts->
  return n;
}

void warehouse_checkout(warehouse_t *wh, char *cart)
{
  // TODO: Stub
  (void) wh;
  (void) cart;
}
