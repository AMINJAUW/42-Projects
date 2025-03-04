/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:17:36 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/08 21:13:54 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint32_t invert_endian(uint32_t value) {
    return ((value >> 24) & 0xFF) |       // Move byte 3 to byte 0
            ((value >> 8) & 0xFF00) |      // Move byte 2 to byte 1
            ((value << 8) & 0xFF0000) |    // Move byte 1 to byte 2
            ((value << 24) & 0xFF000000);  // Move byte 0 to byte 3
}

static size_t calculate_blocks(size_t byte_len) {
    size_t i = 1;
    while(byte_len > (i * 64) - 8 - 1) //need at least one '1' at the end of the message
        i++;
    return i;
}

static u_int32_t **initalize_matrix(size_t nbr_blocks) {
    
    u_int32_t **matrix = ft_calloc(nbr_blocks + 1, sizeof(u_int32_t *));
    if (matrix == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < nbr_blocks; i++) {
        matrix[i] = ft_calloc(16 + 1, sizeof(uint32_t));
        if (matrix[i] == NULL) {
            for (size_t j = 0; j < i; j++)
                ft_free(matrix[j]);
            ft_free(matrix);
            return NULL;
        }
    }
    return matrix;
}

u_int32_t **create_input_matrix(char *input, bool big_endian) {
    size_t byte_len = ft_strlen(input);
    size_t nbr_blocks = calculate_blocks(byte_len);
    u_int32_t **matrix = initalize_matrix(nbr_blocks);
    if (matrix == NULL)
        return NULL;

    size_t block_index, word_index, byte_index;

    for (size_t i = 0; i < byte_len; i++){
        block_index = i / 64; //64 bytes per block
        word_index  = (i % 64) / 4; //4 bytes per word
        byte_index  =  i % 4;

        //adding each byte to it's right place with the |= wich just set the bits to 1
        //The casting to unsigned char is probably unnecessary expect if we give a string with big char like "\x80"
        matrix[block_index][word_index] |= (uint32_t)(unsigned char)input[i] << (8 * byte_index);
        if (big_endian && byte_index == 3)
            matrix[block_index][word_index] = invert_endian(matrix[block_index][word_index]);
    }
    block_index = byte_len / 64;
    word_index = (byte_len % 64) / 4;
    byte_index = byte_len % 4;
    
    // We place the byte 1000 0000 = 0x80 right after the last byte added
    matrix[block_index][word_index] |= (uint32_t)0x80 << (8 * byte_index);
    // The Rest is already filled with 0 thanks to calloc
    if (big_endian)
        matrix[block_index][word_index] = invert_endian(matrix[block_index][word_index]);
        
    u_int64_t bit_len = ((u_int64_t)byte_len) * 8;
    // Split bit_len into low and high 32-bit parts
    uint32_t low_bits = (uint32_t)(bit_len & 0xFFFFFFFF);
    uint32_t high_bits = (uint32_t)(bit_len >> 32);

    // Store the converted values in the last two positions
    matrix[nbr_blocks - 1][14] = big_endian ? high_bits : low_bits;   // Least significant 32 bits
    matrix[nbr_blocks - 1][15] = big_endian ? low_bits : high_bits;  // Most significant 32 bits
    
    return matrix;
}
