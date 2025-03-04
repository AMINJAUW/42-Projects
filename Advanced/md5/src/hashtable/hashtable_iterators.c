/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_iterators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:45:57 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/02 14:53:45 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

// Return new hash table iterator (for use with ht_next).
t_hashtable_iterator ht_iterator(const t_hashtable* table) {
    t_hashtable_iterator it;
    it._table = table;
    it._index = 0;
    return it;
}

// Move iterator to next item in hash table, update iterator's key
// and value to current item, and return true. If there are no more
// items, return false. Don't call ht_set during iteration.
bool ht_next(t_hashtable_iterator* it) {
    // Loop till we've hit end of entries array.
    const t_hashtable* table = it->_table;    
    while (it->_index < table->capacity) {
        size_t i = it->_index;
        it->_index++;
        if (table->entries[i].key != NULL) {
            // Found next non-empty item, update iterator key and value.
            t_hash_entry entry = table->entries[i];
            it->key = entry.key;
            it->value = entry.value;
            return true;
        }
    }
    return false;
}
