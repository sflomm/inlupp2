#pragma once 
#include "../business_logic/webstore_types.h"

/// @brief contains a text based menu of the possible actions for the webstore's backend system.
/// for example: add/remove merch to stock or shopping cart
/// @param warehouse warehouse
void event_loop(warehouse_t *warehouse);
