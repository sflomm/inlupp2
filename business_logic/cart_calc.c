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

shopping_cart_t *warehouse_create_cart(warehouse_t *wh)
{
  wh->carts->count++;  

  shopping_cart_t *cart = calloc(1, sizeof(*cart));
    cart->id = wh->carts->count;
    cart->items = ioopm_hash_table_create(string_knr_hash, string_eq);

    ioopm_list_insert(wh->carts->carts_list, 0, ptr_elem(cart));

    return cart;
}

shopping_cart_t *warehouse_find_shopping_cart(warehouse_t *wh, size_t cart_id, size_t *index) {
  size_t counter = 0;

    ioopm_list_iterator_t *it =
        ioopm_list_iterator_create(wh->carts->carts_list);

    while (!ioopm_list_iterator_at_end(it))
    {
        elem_t value = ioopm_list_iterator_current(it);
        shopping_cart_t *value_cart = value.p;
        if (value_cart->id == cart_id) {
          if (counter != 0) {
            *index = counter;
          }
        ioopm_list_iterator_destroy(it);
        return value_cart;
        }
        ioopm_list_iterator_advance(it);
        counter++;
    }
     ioopm_list_iterator_destroy(it);
      return NULL;
}

void warehouse_remove_cart(warehouse_t *wh, size_t cart_id, size_t *index)
{
  shopping_cart_t *cart = warehouse_find_shopping_cart(wh, cart_id, index);
  ioopm_hash_table_destroy(cart->items);
  ioopm_list_remove(wh->carts->carts_list, *index);
  free(cart);
}

static bool warehouse_merch_exists(warehouse_t *wh, char *merch) {
 if (warehouse_find_merch(wh, merch) != NULL)
    {
      return true;
    } else {
      return false;
}
}

// STÄDA: används aldrig så jag kommenterade bort den
// static bool quant_assert(size_t quant) {
//   if (quant == 0) {
//     return false;
//   }
//   return true;
// }

// FIXME: kan lägga in obegränsat med merch, HAR INTE UPPDATERATS ÄN? så skumt
bool warehouse_add_to_cart(warehouse_t *wh, size_t cart_id,
                            char *merch, size_t quant)
{
//quant cant be less then or equal to zero
  if (quant <= 0) {
    return false;
  }
 //Check if merch exists
  if (!warehouse_merch_exists(wh, merch)) {
    return false;
  }

  size_t index = 0;

  shopping_cart_t *cart = warehouse_find_shopping_cart(wh, cart_id, &index);

  if (cart == NULL) {
    //cart doesnt exist
    return false;
  } else {   //cart exists, insert (hash_table will just replace it if already exits)
       ioopm_hash_table_insert(cart->items, string_elem(merch), size_elem(quant));
       return true;
  }
}

bool warehouse_remove_from_cart(warehouse_t *wh, size_t cart_id,
                                char *merch, size_t quant)
{
  size_t index = 0;
  shopping_cart_t *cart = warehouse_find_shopping_cart(wh, cart_id, &index);

 //Check if merch exists
   if (!warehouse_merch_exists(wh, merch)) {
    return false;
   }

    // Removing zero items is allowed
    if (quant == 0)
    {
        return true;
    }
  
    // Find the current quantity of this merchandise in the cart
    elem_t result;

    if (!ioopm_hash_table_lookup(cart->items, string_elem(merch), &result))
    {
        return false;
    }

    size_t current_quant = result.si;

    // Cannot remove more items than the cart contains
    if (quant > current_quant)
    {
        return false;
    }

    // Remove the merchandise completely
    if (quant == current_quant)
    {
        ioopm_hash_table_remove(cart->items, string_elem(merch));
    }
    else
    {
        // Update the remaining quantity
        ioopm_hash_table_insert(cart->items,
                                string_elem(merch),
                                size_elem(current_quant - quant));
    }

    return true;
}

size_t warehouse_calculate_cost(warehouse_t *wh, size_t cart_id)
{
  size_t price_cart = 0;
  size_t index = 0;
  shopping_cart_t *cart = warehouse_find_shopping_cart(wh, cart_id, &index);
  ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(cart->items);
  while (!ioopm_hash_table_iterator_at_end(it)) {
    //find value and qunatity of merch
    elem_t quantity = ioopm_hash_table_iterator_current_value(it);
    elem_t merch = ioopm_hash_table_iterator_current_key(it);

    //find the pric of the merch and multiply with quantity
    merch_t *price_merch = warehouse_find_merch(wh, merch.s);
    size_t price_with_quant = price_merch->price * quantity.si;

    //add to price of cart
    price_cart = price_cart + price_with_quant;
    ioopm_hash_table_iterator_advance(it);
  }
  ioopm_hash_table_iterator_destroy(it);
  return price_cart;
}

static void remove_shelf_quant(warehouse_t *wh, elem_t merch, elem_t quantity, size_t *remove) {

      merch_t *actual_merch = warehouse_find_merch(wh, merch.s);
      ioopm_list_t *list_locs = actual_merch->locs;
      ioopm_list_iterator_t *lit = ioopm_list_iterator_create(list_locs);
     //keeps track of removed elements
    while ((!ioopm_list_iterator_at_end(lit)) && *remove < quantity.si) {

      elem_t current_shelf = ioopm_list_iterator_current(lit);
      shelf_t *shelf = current_shelf.p;
      
      while (shelf->quant > 0 && *remove < quantity.si) {
        shelf->quant--;
        (*remove)++;
      }
      ioopm_list_iterator_advance(lit);
      }
      ioopm_list_iterator_destroy(lit);
}

bool warehouse_checkout(warehouse_t *wh, size_t cart_id)
{
  // find cart
  size_t index = 0;
    shopping_cart_t *cart = warehouse_find_shopping_cart(wh, cart_id, &index);
     ioopm_hash_table_iterator_t *it = ioopm_hash_table_iterator_create(cart->items);

     //search cart for merch to find quantity
        while (!ioopm_hash_table_iterator_at_end(it)) {
    size_t remove = 0;
    elem_t key = ioopm_hash_table_iterator_current_key(it);
    elem_t quantity = ioopm_hash_table_iterator_current_value(it);
    merch_t *merch_type = warehouse_find_merch(wh, key.s);
    
    // if the quantity of current merch is less then or equal to stock of that merch,
    // remove from all of its shelves
    if (quantity.si <= merch_type->stock) { // STÄDA: gamla koden var (0 <= quantity.si && quantity.si <= merch_type->stock)
                                            // jag tog bort första villkoret då size_t alltid är positivt. testerna funkar
    remove_shelf_quant(wh, key, quantity, &remove);
    //this should always be true, else something went wrong
    if (remove == quantity.si) {
    merch_type->stock -= remove;
    ioopm_hash_table_iterator_advance(it);
    } else {
      ioopm_hash_table_iterator_destroy(it);
      return false;
    }
} else {
      ioopm_hash_table_iterator_destroy(it);
      return false;
    }
}
    warehouse_remove_cart(wh, cart_id, &index);
    ioopm_hash_table_iterator_destroy(it);
    return true;
}
