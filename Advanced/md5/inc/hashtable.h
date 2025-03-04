/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:55:31 by aminjauw          #+#    #+#             */
/*   Updated: 2024/12/28 12:05:59 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# define INITIAL_CAPACITY 16
// Values used for the Hashing of the key
# define FNV_OFFSET 14695981039346656037UL
# define FNV_PRIME 1099511628211UL

# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>

typedef enum e_status {
	FAIL,
	SUCCESS,
} t_status;

typedef struct s_hash_entry {
    char  *key;
    void        *value;
} t_hash_entry;

typedef struct s_hashtable {
    t_hash_entry    *entries;
    size_t          length;
    size_t          capacity;
} t_hashtable;

typedef struct s_hashtable_iterator{
    const char          *key;
    const void          *value;   
       
    const t_hashtable   *_table;
    size_t              _index;
} t_hashtable_iterator;


t_hashtable *ht_create(void);
void        ht_destroy(t_hashtable *table);
void        ht_free_values(t_hashtable *table);
void        *ht_get(const t_hashtable* table, const char* key);
const char  *ht_set(t_hashtable* table, const char* key, void* value);
char        **ht_keys(const t_hashtable *table);
bool        is_already_key(const t_hashtable *table, const char* key);

t_hashtable_iterator ht_iterator(const t_hashtable* table);
bool ht_next(t_hashtable_iterator* it);

uint64_t    hash_key(const char* key);
void	    *ft_calloc(size_t nmemb, size_t size);
void	    ft_free(void *addr);
t_status    is_equal(const char *s1, const char *s2);
char    	*ft_strdup(const char *s1);
void	    free_string_array(char **array);

#endif