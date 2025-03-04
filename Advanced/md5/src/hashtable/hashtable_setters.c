/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_setters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:16:16 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/07 17:14:37 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

// Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
uint64_t hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

static const char* ht_set_entry(t_hash_entry* entries, t_hashtable *table,
        const char* key, void* value) {
    
    uint64_t hash = hash_key(key);
    size_t index = hash % table->capacity;

    // Loop till we find an empty entry.
    // Impossible not have a least one because of expand
    while (entries[index].key != NULL) {
        if (is_equal(key, entries[index].key) == SUCCESS) {
            entries[index].value = value;
            return key;
        }
        // Key wasn't in this slot, move to next (linear probing).
        index++;
        if (index >= table->capacity) {
            index = 0;
        }
    }

    // Didn't find key, copy then insert it.
    char *key_copy = ft_strdup(key);
    if (key_copy == NULL) {
        return NULL;
    }
    table->length++;
    entries[index].key = key_copy;
    entries[index].value = value;
    return key_copy;
}

static bool ht_expand(t_hashtable* table) {
    size_t new_capacity = table->capacity * 2;
    if (new_capacity < table->capacity) {
        return false;  // overflow
    }
    t_hash_entry* new_entries = ft_calloc(new_capacity, sizeof(t_hash_entry));
    if (new_entries == NULL) {
        return false;
    }

    // Iterate entries, move all non-empty ones to new table's entries.
    for (size_t i = 0; i < table->capacity; i++) {
        t_hash_entry entry = table->entries[i];
        if (entry.key != NULL) {
            ht_set_entry(new_entries, table, entry.key, entry.value);
        }
    }

    // Free old entries array and update this table's details.
    ft_free(table->entries);
    table->entries = new_entries;
    table->capacity = new_capacity;
    return true;
}

bool is_already_key(const t_hashtable *table, const char* key) {
    uint64_t hash = hash_key(key);
    size_t index = hash % table->capacity;
    size_t init_index = hash % table->capacity;
    
    while (table->entries[index].key != NULL) {
        if (is_equal(key, table->entries[index].key) == SUCCESS) {
            return true;
        }
        // Key wasn't in this slot, move to next (linear probing).
        index++;
        if (index >= table->capacity) {
            index = 0;
        }
        if (index == init_index) {
            return false;
        }
    }
    return false;
}

// Return the key set or NULL in case of error
// hard copy specify if the value needs to be hard copied
const char  *ht_set(t_hashtable* table, const char* key, void* value) {
    if (value == NULL) {
        return NULL;
    }
    // If length will exceed half of current capacity and if it is a new key, expand it.
    if (table->length + 1 >= table->capacity / 2 && !is_already_key(table, key)) {
        if (!ht_expand(table)) {
            return NULL;
        }
    }

    return ht_set_entry(table->entries, table, key, value);
}