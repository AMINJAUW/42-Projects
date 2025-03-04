/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_getters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:19:38 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/04 11:23:11 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

void    *ht_get(const t_hashtable* table, const char* key) {
    uint64_t hash = hash_key(key);
    size_t index = hash % table->capacity;
    //to prevent inifinit loop when the hash is full and we are looking for a new key
    size_t init_index = index; 

    // Loop till we find an empty entry.
    while (table->entries[index].key != NULL) {
        if (is_equal(key, table->entries[index].key) == SUCCESS) {
            return table->entries[index].value;
        }
        // Key wasn't in this slot, move to next (linear probing).
        index++;
        if (index >= table->capacity) {
            // At end of entries array, wrap around.
            index = 0;
        }
        if (index == init_index)
            return NULL;
    }
    return NULL;
}

//Retrun a hard copy of the keys in an array
char    **ht_keys(const t_hashtable *table) {
    char **keys = ft_calloc(table->length + 1, sizeof(char *));
    if (keys == NULL)
        return NULL;
    
    for (size_t i = 0, j = 0; i < table->capacity; i++) {
        if (table->entries[i].key) {
            keys[j] = ft_strdup(table->entries[i].key);
            if (keys[j] == NULL) {
                free_string_array(keys);
                return NULL;
            }
            j++;
        }
    }
    return keys;
}