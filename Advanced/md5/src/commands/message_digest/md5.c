/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:16:27 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/07 22:41:24 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_ssl.h"

static void to_big_endian(u_int32_t *little_endian_values) {
    for (size_t i = 0; i < 4; i++) {
        little_endian_values[i] = 
            ((little_endian_values[i] & 0xFF) << 24) | 
            ((little_endian_values[i] & 0xFF00) << 8) | 
            ((little_endian_values[i] & 0xFF0000) >> 8) | 
            ((little_endian_values[i] & 0xFF000000) >> 24);
    }
}

static u_int32_t rotl32 (u_int32_t value, unsigned int count) {
    return (value << count) | (value >> (32 - count));
}

static u_int32_t F(u_int32_t B, u_int32_t C,u_int32_t D) {
    return (B & C) | ((~B) & D);
}
static u_int32_t G(u_int32_t B, u_int32_t C,u_int32_t D) {
    return (D & B) | ((~D) & C);
}
static u_int32_t H(u_int32_t B, u_int32_t C,u_int32_t D) {
    return (B ^ C ^ D);
}
static u_int32_t I(u_int32_t B, u_int32_t C,u_int32_t D) {
    return (C ^ (B | (~D)));
}

void 	md5(u_int32_t **input_matrix, u_int32_t *hash_output) {


    static const uint32_t K[64] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };
    
    // MD5 S-Table for shift amounts
    static const uint32_t s[64] = {
        7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
        5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
        4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
        6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
    };


    // Precomputed K constants based on the binary integer part of the sines of integers
        
    // Initialize variables:
    hash_output[0] = 0x67452301;   // A0
    hash_output[1] = 0xefcdab89;   // B0
    hash_output[2] = 0x98badcfe;   // C0
    hash_output[3] = 0x10325476;   // D0

    for (size_t i = 0; input_matrix[i] != NULL; i++) {
        u_int32_t A = hash_output[0];
        u_int32_t B = hash_output[1];
        u_int32_t C = hash_output[2];
        u_int32_t D = hash_output[3];

        for (size_t j = 0; j < 64; j++) {
            
            u_int32_t operation = 0;
            size_t g;
            switch (j/16)
            {
            case 0:
                g = j % 16;
                operation = A + F(B,C,D) + input_matrix[i][g] + K[j];
                break;
            case 1:
                g = ((5 * j) + 1) % 16;
                operation = A + G(B,C,D) + input_matrix[i][g] + K[j];
                break;
            case 2:
                g = ((3 * j) + 5) % 16;
                operation = A + H(B,C,D) + input_matrix[i][g] + K[j];
                break;
            case 3:
                g = (7 * j) % 16;
                operation = A + I(B,C,D) + input_matrix[i][g] + K[j];
                break;
            
            default:
                break;
            }
            
            A = D;
            D = C;
            C = B;
            B = B + rotl32(operation, s[j]);
        }
        hash_output[0] += A;
        hash_output[1] += B;
        hash_output[2] += C;
        hash_output[3] += D;

    }
    to_big_endian(hash_output);
}
