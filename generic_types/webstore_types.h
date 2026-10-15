#pragma once
#include "common.h"
#include "linked_list.h"

typedef struct merch merch_t;
typedef struct shelf shelf_t;
typedef struct warehouse warehouse_t;

struct merch {
    char *name;
    char *desc;
    size_t price;
    ioopm_list_t *locs;
};

struct shelf {
    char *shelf;
    size_t quant;
};

struct warehouse {
    ioopm_hash_table_t *merch_ht;
    ioopm_hash_table_t *location_ht;
};