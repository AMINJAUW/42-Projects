/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:34:13 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/08 22:42:21 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static u_int32_t right_rotate(u_int32_t n, size_t times) {
    return (n >> times) | (n << (32 - times)); 
}
void 	sha256(u_int32_t **input_matrix, u_int32_t *hash_output) {
   static u_int32_t k[64] = {
   0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    
    u_int32_t w[64] = {0}; //
    
    hash_output[0] = 0x6a09e667;
    hash_output[1] = 0xbb67ae85;
    hash_output[2] = 0x3c6ef372;
    hash_output[3] = 0xa54ff53a;
    hash_output[4] = 0x510e527f;
    hash_output[5] = 0x9b05688c;
    hash_output[6] = 0x1f83d9ab;
    hash_output[7] = 0x5be0cd19;

    u_int32_t vars[8] = {0};

    for (size_t i = 0; input_matrix[i]; i++) {
        for (size_t j = 0; j < 16; j++) {
            w[j] = input_matrix[i][j];
        }
        for (size_t j = 16; j < 64; j++) {
            u_int32_t s0 = right_rotate(w[j - 15], 7) ^ right_rotate(w[j - 15], 18) ^ (w[j - 15] >> 3);
            u_int32_t s1 = right_rotate(w[j - 2], 17) ^ right_rotate(w[j - 2], 19) ^ (w[j - 2] >> 10);
            w[j] = w[j - 16] + s0 + w[j - 7] + s1;
        }
        for (size_t a = 0; a < 8; a++) {
            vars[a] = hash_output[a];
        }

        for (size_t j = 0; j < 64; j++) {
            u_int32_t S1 = right_rotate(vars[4], 6) ^ right_rotate(vars[4], 11) ^ right_rotate(vars[4], 25);
            u_int32_t ch = (vars[4] & vars[5]) ^ ((~vars[4]) & vars[6]);
            u_int32_t temp1 = vars[7] + S1 + ch + k[j] + w[j];
            u_int32_t S0 = right_rotate(vars[0], 2) ^ right_rotate(vars[0], 13) ^ right_rotate(vars[0], 22);
            u_int32_t maj = (vars[0] & vars[1]) ^ (vars[0] & vars[2]) ^ (vars[1] & vars[2]);
            u_int32_t temp2 = S0 + maj;
            
            vars[7] = vars[6];
            vars[6] = vars[5];
            vars[5] = vars[4];
            vars[4] = vars[3] + temp1;
            vars[3] = vars[2];
            vars[2] = vars[1];
            vars[1] = vars[0];
            vars[0] = temp1 + temp2;  
        }
        
        for (size_t j = 0; j < 8; j++)
            hash_output[j] += vars[j];        
    }
}