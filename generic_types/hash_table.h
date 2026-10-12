#include  <stdbool.h>
#include "common.h"
#pragma once

/**
* @file hash_table.h
* @author Simon Funke, Max Björbaek Andersson
* @date 2026-09-01
* @brief Simple hash table that maps string keys to integer values.
*
* Here typically goes a more extensive explanation of what the header
* defines. Doxygens tags are words preceeded by either a backslash @\
* or by an at symbol @@.
*
*/

typedef struct hash_table ioopm_hash_table_t;

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
/// @param key a key to be looked up
/// @return true or false
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief check if a hash table is empty
/// @param a hashtable
/// @return true or false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief calculates the table size of the hash table 
/// @param a hashtable
/// @return the table size as a integer
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);

/// @brief Create a new hash table
/// @param a hash function
/// @param a equals function
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key
elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);

