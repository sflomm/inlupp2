#pragma once 
#include "../business_logic/webstore_types.h"


/// @brief lists all current merch 20 at a time
/// @param merch_ht hashtable that holds all merch
void warehouse_list_merch(warehouse_t *wh);

void warehouse_show_stock(warehouse_t *wh, char *key);

void event_loop(warehouse_t *warehouse);
