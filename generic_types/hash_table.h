#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "common.h"

/**
* @file hash_table.h
* @author Ludvig Zeitler, Ella Odlander
* @date 18/9 2026
* @brief Simple hash table that maps string keys to integer values.
*
* Here typically goes a more extensive explanation of what the header
* defines. Doxygens tags are words preceeded by either a backslash @\
* or by an at symbol @@.
*
*/

typedef struct hash_table ioopm_hash_table_t;

/// @brief Create a new hash table with homogenous keys
/// @param hash_fn hash function that specifies type of key-elements
/// @param key_eq_fn a function for checking equality of keys
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
/// @param result a pointer in which to store the value of the key
/// @return true if key was found, false if not (FIXME: what if the key does not exist?)
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key (FIXME: what if the key does not exist?)
elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);

/// @brief looks through hash table for key
/// @param ht hash table operated upon
/// @param key key to check for
/// @return true if key was found
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief checks if size of hash table is zero
/// @param ht hash table operated upon
/// @return true if empty, otherwise false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief counts every entry in a hash table
/// @param ht hash table operated upon
/// @return size of the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);

/// @brief creates a hashtable with a dynamic size
/// @param hash_fn hash function that specifies type of key-elements
/// @param key_eq_fn a function for checking equality of keys
/// @param load_factor load factor for the hash table
/// @param capacity capacity of the hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create_dynamic(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn, size_t capacity, double load_factor);
