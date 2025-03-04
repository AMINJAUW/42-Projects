/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 19:19:43 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/09 13:44:01 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

size_t array_size(char const* const* array) {
	size_t i = 0;
	if (array == NULL)
		return 0;
	while (array[i] != NULL) {
		i++;
	}
	return i;
}

t_status is_equal(const char *s1, const char *s2) {
	if ((s1 == NULL) != (s2 == NULL))
		return FAIL;
	if (s1 == NULL && s2 == NULL)
		return SUCCESS;

	if (ft_strlen(s1) != ft_strlen(s2))
		return FAIL;

	int i;
	i = 0;

	while (s1[i] && s1[i] == s2[i])
		i++;
	return s1[i] == '\0' ? SUCCESS : FAIL;
}

int ft_strlen(const char *str) {
	if (str == NULL)
		return 0;

	int i = 0;
	
	while (str[i])
		i++;
	return i;
}

void write_str(const char *str) {
	write(STDOUT_FILENO, str, ft_strlen(str));
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = ft_strlen((char *)s1);
	dup = ft_calloc((len + 1), sizeof(char));
	if (!dup)
		return (0);
	i = 0;
	while (i <= len)
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
}
//Free multidimientional array, choosing if smallest elements need to be ft_free
void	free_string_array(char **array) {
	if (array == NULL)
		return;
	for (size_t i = 0; array[i] != NULL; i++) {
		ft_free(array[i]);
	}
	ft_free(array);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*pwd;
	size_t	i;

	i = 0;
	pwd = malloc(nmemb * size);
	if (! pwd)
		return (0);
	while (i < nmemb * size)
	{
		pwd[i] = 0;
		i ++;
	}

	return (pwd);
}

void	ft_free(void *addr){

	free(addr);
}

void	clear_memory(t_hashtable *commands, t_command_line command_line) {
	ht_free_values(commands);
	ht_destroy(commands);
	ft_free(command_line.files);

	free_string_array(command_line.input_str);

	ht_free_values(command_line.options);
	ht_destroy(command_line.options);
}

bool is_option_set(const t_hashtable *options, const char *key) {
	bool *value = (bool *)ht_get(options, key);
	return *value;
}

bool is_str_in_arr(const char * const *array, const char *str) {
	for (int i = 0; array[i] != NULL; i++) {
		if (is_equal(str, array[i]))
			return true;
	}
	return false;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*source;	

	if (!src && !dst)
		return (dst);
	dest = (char *)dst;
	source = (const char *)src;
	i = 0;
	while (i < n)
	{
		dest[i] = source[i];
		i ++;
	}
	return (dst);
}

void	ft_memset(char *dst, char value, size_t size) {
	if (dst == NULL)
		return;
	for (size_t i = 0; i < size; i++) {
		dst[i] = value;
	}
}