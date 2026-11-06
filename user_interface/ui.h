#pragma once 
#include "../business_logic/webstore_types.h"

/**
* @file ui.h
* @author Ella Odlander & Simon Funke
* @date 6/11 2026
* @brief the function needed to run the main program, 
* the rest of the functions in ui.c needs user input and is therefore not tested with cunit.
*/

/// @brief contains a text based menu of the possible actions for the webstore's backend system.
/// for example: add/remove merch to stock or shopping cart
/// @param warehouse warehouse
void ioopm_event_loop(warehouse_t *warehouse);
