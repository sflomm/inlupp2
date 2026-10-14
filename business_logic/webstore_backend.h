#pragma once
typedef struct warehouse warehouse_t;

/// @brief 
/// @param 
/// @param 
/// @return
warehouse_t *warehouse_create();


/// @brief 
/// @param 
/// @param 
/// @return
void warehouse_destroy(warehouse_t *wh);


/// @brief 
/// @param 
/// @param 
/// @return
void warehouse_add_merch(char *name, char *desc, int price, warehouse_t *wh);

/// @brief 
/// @param 
/// @param 
/// @return
void warehouse_list_merch(warehouse_t *wh);


/// @brief 
/// @param 
/// @param 
/// @return
void warehouse_remove_merch(warehouse_t *wh, char *key);


/// @brief 
/// @param 
/// @param 
/// @return
void warehouse_edit_merch();


/// @brief 
/// @param 
/// @param 
/// @return
void warehouse_show_stock();


/// @brief 
/// @param 
/// @param 
/// @return
void warehouse_replenish_stock();



/// @brief 
/// @param 
/// @param 
/// @return
void warehouse_create_cart();


/// @brief 
/// @param 
/// @param 
/// @return
void warehouse_remove_cart();


/// @brief 
/// @param 
/// @param 
/// @return
void warehouse_add_to_cart(elem_t cart, char *key);

/// @brief 
/// @param 
/// @param 
/// @return
void warehouse_remove_from_cart();

/// @brief 
/// @param 
/// @param 
/// @return
void warehouse_calculate_cost();

/// @brief 
/// @param 
/// @param 
/// @return
void warehouse_checkout();
