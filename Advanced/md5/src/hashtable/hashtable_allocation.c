/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_allocation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:17:36 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/02 15:51:56 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

t_hashtable *ht_create(void) {
    t_hashtable *table = ft_calloc(1, sizeof(t_hashtable));
    if (table == NULL)
        return NULL;
    
    table->length = 0;
    table->capacity = INITIAL_CAPACITY;
    
    table->entries = ft_calloc(table->capacity, sizeof(t_hash_entry));
    if (table->entries == NULL) {
        ft_free(table);
        return NULL;
    }
    return table;
}

void    ht_destroy(t_hashtable *table) {
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->entries[i].key) {
            ft_free(table->entries[i].key);  
        }
    }
    ft_free(table->entries);
    ft_free(table);
}

void    ht_free_values(t_hashtable *table) {
    for (size_t i = 0; i < table->capacity; i++) {
        if (table->entries[i].key) {
            ft_free(table->entries[i].value);  
        }
    }
}