/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:35:01 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/07 21:45:29 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void to_hex(u_int32_t n, char *dest) {
    static char hex[16] = "0123456789abcdef";
    
    for (int i = 7; i >= 0; i--) {
        dest[i] = hex[n & 0xF];
        n >>= 4;
    }
}

char *format_hex_hash(u_int32_t *buffer, char *hex_hash, size_t size) {
	for (size_t i = 0; i < size; i++){
		to_hex(buffer[i], &(hex_hash[i * 8]));
	}
	return hex_hash;
}