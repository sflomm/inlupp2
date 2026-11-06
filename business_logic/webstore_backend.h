#pragma once

#include "webstore_types.h"
#include "../generic_types/hash_table_struct.h"
#include "../generic_types/linked_list_struct.h"
#include "../generic_types/common.h"

/**
* @file webstore_backend.h
* @author Ella Odlander & Simon Funke
* @date 6/11 2026
* @brief functions needed to run main program and are tested in webstore_backend_tests.c 
*/

typedef struct warehouse warehouse_t;

// merch_stock.c FUNCTIONS

/// @brief creates an empty warehouse
/// @return a warehouse_t which hold 2 hashtables (merch & location) and a carts struct
warehouse_t *warehouse_create();

/// @brief frees the warehouse's allocated memory 
/// @param wh the warehouse to be deleted
void warehouse_destroy(warehouse_t *wh);

/// @brief find specific merch
/// @param wh warehouse struct
/// @param key merch's key
/// @return the desired merch or NULL if not found
merch_t *warehouse_find_merch(warehouse_t *wh, char *key);

/// @brief add merch to the hashtable merch_ht
/// @note  caller owns name and desc 
/// @param wh warehouse struct
/// @param name merch's name
/// @param desc merch's description
/// @param price merch's price
void warehouse_add_merch(warehouse_t *wh, char *name, char *desc, size_t price);

/// @brief remove merch from warehouse and it's stock
/// @param wh warehouse
/// @param key key to remove
/// @return true if removed, false if not
bool warehouse_remove_merch(warehouse_t *wh, char *key);

/// @brief edit merch's name, description or/and price.
/// @note  stock is not affected. Caller owns key, new_name and new_desc.
/// @param wh warehouse
/// @param key merch to be edited
/// @param new_name merch's new name
/// @param new_desc merch's new description
/// @param new_price merch's new price
/// @return true if successfull edit, false if not 
bool warehouse_edit_merch(warehouse_t *wh, char *key, char *new_name, char* new_desc, size_t new_price);

/// @brief find specific shelf
/// @param list list of shelves (stored in merch->locs)
/// @param shelf desired shelf
/// @return the desired shelf or NULL if not found
shelf_t *warehouse_find_shelf(ioopm_list_t *list, char *shelf);

/// @brief increase stock of a merch by at least one
/// @note  caller owns shelf
/// @param wh warehouse 
/// @param shelf desired shelf
/// @param merch desired merch to increase
/// @param quant quantity to add
void warehouse_replenish_stock(warehouse_t *wh, char *shelf, merch_t *merch, size_t quant);

// cart_calc.c FUNCTIONS

/// @brief creates a new shopping cart to the warehouse's hashtable for shopping carts
/// @param wh warehouse that holds hashtable cart_ht
/// @return a hashtable where key is merch's name and value it's quantity
shopping_cart_t *warehouse_create_cart(warehouse_t *wh);

/// @brief Finds the shopping cart by traversing the shopping carts in the warehouse
/// @param wh The warehouse that holds shopping carts
/// @param cart_id shopping cart's identifier
/// @param index ???
/// @return a shopping cart or NULL if not found
shopping_cart_t *warehouse_find_shopping_cart(warehouse_t *wh, size_t cart_id, size_t *index);

/// @brief removes a shopping cart from the system
/// @param wh warehouse
/// @param cart_id shopping cart's identifier, cart to be removed
/// @param index ???
void warehouse_remove_cart(warehouse_t *wh, size_t cart_id, size_t *index);

/// @brief add some quantity of merch to specific shopping cart
/// @param wh warehouse
/// @param cart_id shopping cart's identifier
/// @param merch desired merch to add
/// @param quant quantity to be added
/// @return true if merch is added to cart, false if not
bool warehouse_add_to_cart(warehouse_t *wh, size_t cart_id, char *merch, size_t quant);

/// @brief removes zero or more items of some merch from specific shopping cart
/// @param wh warehouse 
/// @param cart_id shopping cart's identifier
/// @param merch desired merch to remove
/// @param quant quantity to be removed
/// @return true if merch was removed from cart, false if not
bool warehouse_remove_from_cart(warehouse_t *wh, size_t cart_id, char *merch, size_t quant);

/// @brief calculate cost of a shopping cart 
/// @param wh warehouse
/// @param cart_id shopping cart's identifier
/// @return the cost (positive integer) of all merch in the shopping cart
size_t warehouse_calculate_cost(warehouse_t *wh, size_t cart_id);

/// @brief user goes through purchase of all merch in specific shopping cart.
/// the stock for the merches of the cart is decreased and shopping cart is removed from system
/// @param wh warehouse
/// @param cart_id shopping cart's identifier
/// @return true if successfully checked out, else false
bool warehouse_checkout(warehouse_t *wh, size_t cart_id);