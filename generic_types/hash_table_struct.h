#include "common.h"
#define No_Buckets 17

typedef struct entry entry_t;

struct entry
{
  elem_t key;     // holds the key
  elem_t value;     // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  ioopm_eq_function *key_eq_fn;
  ioopm_hash_function *hash_fn;
  entry_t buckets[No_Buckets]; // size dependent on macro No_Buckets
};

struct hash_table_iterator
{
  ioopm_hash_table_t *ht;
  size_t current_bucket;
  entry_t *current_entry;
};
