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
bool warehouse_add_to_cart(warehouse_t *wh, size_t cart_id,
                           char *merch, size_t quant)
{
  //quant cant be zero
  assert(quant_assert(quant));
    // merch must exist
    assert(warehouse_merch_exists(wh, merch));

// bool warehouse_add_to_cart(warehouse_t *wh, size_t cart_id,
//                            char *merch, size_t quant)
// {
//   //quant cant be less then or equal to zero
//   assert(quant_assert(quant));
//     // Check if merch exists
//     if (!warehouse_merch_exists(wh, merch)) {
//       return false;
//     }

//     ioopm_list_iterator_t *it =
//         ioopm_list_iterator_create(wh->carts->carts_list);

//     while (!ioopm_list_iterator_at_end(it))
//     {
//         elem_t value = ioopm_list_iterator_current(it);
//         shopping_cart_t *value_cart = value.p;

            ioopm_list_iterator_destroy(it);
            return true;
            
//         }

//         ioopm_list_iterator_advance(it);
//     }
    
    //cart doesnt exist
    ioopm_list_iterator_destroy(it);
    return false;
}

static shopping_cart_t *warehouse_find_shopping_cart(warehouse_t *wh, char *key)
{
  ioopm_hash_table_t *ht = 
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
      ioopm_hash_table_iterator_advance(it);
    }
  }
  return NULL;
}

void warehouse_remove_from_cart(warehouse_t *wh, size_t cart_id, char *merch, size_t quant)
{
  //quant cant be zero
  assert(quant_assert(quant));
  //merch must exist
  assert(warehouse_merch_exists(wh, merch));

      ioopm_list_iterator_t *it =
        ioopm_list_iterator_create(wh->carts->carts_list);

    while (!ioopm_list_iterator_at_end(it))
    {
        elem_t value = ioopm_list_iterator_current(it);
        shopping_cart_t *value_cart = value.p;

        if (value_cart->id == cart_id)
        {
            if (warehouse_merch_exists(wh, merch)) {
            merch_t *merch = warehouse_find_merch(value_cart->items, merch);
            merch->
          }
            ioopm_list_iterator_destroy(it);
            return true;

}

size_t warehouse_calculate_cost(ioopm_hash_table_t *cart_ht, char *cart)
{
  // TODO: Stub
  (void) cart_ht;
  (void) cart;
  size_t n = 0;
  return n;
}

void warehouse_checkout(warehouse_t *wh, char *cart)
{
  // TODO: Stub
  (void) wh;
  (void) cart;
}
