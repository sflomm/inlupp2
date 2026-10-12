#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "hash_table_struct.h"


// STATIC FUNCTIONS

// Creates an entry
static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));
  
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;
  
  return new_entry;
}

// Destroys an entry and its key, and returns the next pointer of the entry removed
static entry_t *entry_destroy(entry_t *to_remove)
{
  entry_t *next = to_remove->next;
  free(to_remove);
  return next;  
}

// Returns pointer to previous entry or returns pointer to last entry if key not found
static entry_t *find_previous_entry(ioopm_hash_table_t *ht, elem_t key)
{
  // find bucket
  size_t bucket = ht->hash_fn(key) % No_Buckets;
  entry_t *previous = &ht->buckets[bucket]; //starts at sentinel node
  entry_t *current = previous->next;
  
  while (current != NULL && !(ht->key_eq_fn(current->key, key)))
  {
    previous = current;
    current = current->next;
  }

  return previous;
}

// Frees up allocated memory of a linked list from entry onwards
static void destroy_linked_list(entry_t *entry)
{
  entry_t *next = entry_destroy(entry);

  while (next != NULL)
  {
    next = entry_destroy(next);
  }
}


// IOOPM FUNCTIONS

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn)
{
    ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
    ht->hash_fn = hash_fn;
    ht->key_eq_fn = key_eq_fn;
    return ht;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) 
{
    for (int i = 0; i < No_Buckets; i++)
    {
      if (ht->buckets[i].next != NULL)
      {
        destroy_linked_list(ht->buckets[i].next);
      }
    }
  free(ht);
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
  entry_t *previous = find_previous_entry(ht, key);

  // if key exists, update the value, otherwise create a new entry
  if (previous->next != NULL)
  {
    previous->next->value = value;
  }
  else
  {
    previous->next = entry_create(key, value, NULL); // entry is in heap
  }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result)
{
  entry_t *previous = find_previous_entry(ht, key);

  // if the key exists, return the value, otherwise the lookup failed
  if (previous->next != NULL)
  {
    *result = previous->next->value;
    return true;
  }
  else
  {
    return false;
  }
}

elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
{
  entry_t *previous = find_previous_entry(ht, key);
  entry_t *to_remove = previous->next;

  // if key exists
  if (to_remove != NULL)
  {
    elem_t to_remove_int = previous->next->value;
    entry_t *next = entry_destroy(to_remove);
    previous->next = next; // remove entry and update previous entry's next-pointer 
    return to_remove_int; // return value of removed entry
  }
  return int_elem(0); //returns 0 if key was not found. FIXME: what if entry has value 0?
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
  elem_t result;
  return ioopm_hash_table_lookup(ht, key, &result);
}

static size_t bucket_size(entry_t *entry)
{
  size_t size = 0;
  while(entry != NULL)
  {
    ++size;
    entry = entry->next; 
  }
  return size;
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  size_t size = 0;
  for (int i = 0; i < No_Buckets; i++) {
    size += bucket_size(ht->buckets[i].next);
  }
  return size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  size_t ht_size = ioopm_hash_table_size(ht);
  
  if (ht_size == 0)
  {
    return true;
  }
  
  return false;
}
