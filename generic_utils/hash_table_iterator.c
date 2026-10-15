#include "../generic_types/hash_table_iterator.h"
#include "../generic_types/hash_table_struct.h"
#include <assert.h>
#include <stdlib.h>
#include "../generic_types/common.h"

static void advance_iterator_state(ioopm_hash_table_iterator_t *it)
{
    // advance to the next entry in the bucket
    it->current_entry = it->current_entry->next;

    // if it was null advance to the next bucket
    if (it->current_entry == NULL)
    {
        it->current_bucket += 1;

        // if the next bucket existed, update the current entry
        if (it->current_bucket < it->ht->capacity)
        {
            it->current_entry = &it->ht->buckets[it->current_bucket];
        }
    }
}

static void skip_sentinel_nodes(ioopm_hash_table_iterator_t *it)
{
    // if bucket exists and current_entry is sentinel node, keep advancing iterator
    while (it->current_bucket < it->ht->capacity &&
            it->current_entry == &it->ht->buckets[it->current_bucket])
    {
        advance_iterator_state(it);
    }
}

ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht)
{
  ioopm_hash_table_iterator_t *it = malloc(sizeof(ioopm_hash_table_iterator_t));
  it->ht = ht;
  it->current_bucket = 0;
  it->current_entry = &ht->buckets[0];
  skip_sentinel_nodes(it);
  return it;
}

void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it)
{
    free(it);
}

bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it)
{
    return it->current_bucket ==  it->ht->capacity;    
}

void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it)
{
    if(!ioopm_hash_table_iterator_at_end(it))
    {
        //advance iterator
        advance_iterator_state(it);

        // if advancement above leads to sentinel node, skip until next entry/end
        if (it->current_entry == &it->ht->buckets[it->current_bucket])
        {
            skip_sentinel_nodes(it);
        }
    }
}

elem_t ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it)
{
    elem_t current_key = it->current_entry->key;
    return current_key;
}

elem_t ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it)
{
    elem_t current_value = it->current_entry->value;
    return current_value;
}