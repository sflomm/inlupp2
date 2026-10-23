#pragma once

#include "webstore_types.h"
#include "../generic_types/hash_table_struct.h"
#include "../generic_types/linked_list_struct.h"
#include "../generic_types/common.h"

typedef struct warehouse warehouse_t;

// merch_stock.c FUNCTIONS (1-6)

/// @brief creates an empty warehouse
/// @return a warehouse_t which hold 3 hashtables: merch, location and cart
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
/// @param wh warehouse struct
/// @param name merch's name
/// @param desc merch's description
/// @param price merch's price
void warehouse_add_merch(warehouse_t *wh, char *name, char *desc, size_t price);

/// @brief lists all current merch 20 at a time
/// @param merch_ht hashtable that holds all merch
void warehouse_list_merch(ioopm_hash_table_t *merch_ht);

/// @brief remove merch from warehouse and it's stock
/// @param wh warehouse
/// @param key key to remove
/// @return true if removed, false if not
bool warehouse_remove_merch(warehouse_t *wh, char *key);

/// @brief edit merch's name, description or/and price.
/// NOTE. stock is not affected and changing name to existing key is not allowed.
/// @param wh warehouse
/// @param key merch to be edited
/// @param new_name merch's new name
/// @param new_desc merch's new description
/// @param new_price merch's new price
void warehouse_edit_merch(warehouse_t *wh, char *key, char *new_name, char* new_desc, size_t new_price);

/// @brief list all storage locations for particular merch along with quantities 
/// stored on each location
/// @param wh warehouse
/// @param key merch's key
void warehouse_show_stock(warehouse_t *wh, char *key);

/// @brief increase stock of a merch by at least one
/// @param wh warehouse 
/// @param shelf desired shelf
/// @param merch desired merch to increase
/// @param quant quantity to add
/// @return total amount of stock of specific merch
void warehouse_replenish_stock(warehouse_t *wh, char *shelf, merch_t *merch, size_t quant);


// cart_calc.c FUNCTIONS (7-12)

/// @brief creates a new shopping cart to the warehouse's hashtable for shopping carts
/// @param wh warehouse that holds hashtable cart_ht
/// @return a hashtable where key is merch's name and value it's quantity
ioopm_hash_table_t warehouse_create_cart(warehouse_t *wh);

/// @brief removes a shopping cart from the system
/// @param wh warehouse
/// @param key shopping cart to be removed
void warehouse_remove_cart(warehouse_t *wh, char *key);

/// @brief add some quantity of merch to specific shopping cart
/// @param cart_ht hashtable where all shopping carts are stored
/// @param cart desired shopping cart
/// @param merch desired merch to add
/// @param quant quantity to be added
void warehouse_add_to_cart(ioopm_hash_table_t *cart_ht, char *cart, char *merch, size_t quant);

/// @brief removes zero or more items of some merch from specific shopping cart
/// @param cart_ht hashtable where all shopping carts are stored
/// @param cart desired shopping cart
/// @param merch desired merch to remove
/// @param quant quantity to be removed
void warehouse_remove_from_cart(warehouse_t *wh, char *cart, char *merch, size_t quant);

/// @brief calculate cost of a shopping cart 
/// @param cart_ht hash_table where all shopping carts are stored
/// @param cart desired shopping cart
// FIXME: is size_t always an integer?
/// @return the cost (positive integer) of all merch in the shopping cart
size_t warehouse_calculate_cost(ioopm_hash_table_t *cart_ht, char *cart);

/// @brief user goes through purchase of all merch in specific shopping cart
/// the stock for the merches of the cart is decreased and shopping cart is removed from system
/// @param wh warehouse
/// @param cart desired shopping cart
void warehouse_checkout(warehouse_t *wh, char *cart);