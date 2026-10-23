#pragma once
#include "../generic_types/common.h"
#include "../generic_types/linked_list.h"
#include "../generic_types/hash_table.h"
typedef struct merch merch_t;
typedef struct shelf shelf_t;
typedef struct warehouse warehouse_t;
typedef struct shopping_cart shopping_cart_t;
typedef struct carts carts_t;

struct merch {
    char *name;
    char *desc;
    size_t price;
    size_t stock;
    ioopm_list_t *locs;
};

struct shelf {
    char *shelf;
    size_t quant;
};

struct shopping_cart {
    size_t id;
    ioopm_hash_table_t *items; // key = merch name, value = quant
};

struct carts {
    size_t count;
    ioopm_list_t *carts_list;
};

struct warehouse {
    ioopm_hash_table_t *merch_ht;
    ioopm_hash_table_t *location_ht;
    carts_t *carts;
};