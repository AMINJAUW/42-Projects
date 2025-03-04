/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MD_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:18:59 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/08 22:56:46 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void free_matrix(u_int32_t **input_matrix) {
    if (input_matrix == NULL)
        return;
    for (size_t i = 0; input_matrix[i] != NULL; i++) {
        ft_free(input_matrix[i]);
    }
    ft_free(input_matrix);
}

static bool implicit_stdin_read(t_command_line command_line) {
   size_t total_inputs = array_size((const char *const *)command_line.files);
    //only specific case where we have no files or not the "-" file with the -p flag
    if (total_inputs == 0 || 
        (is_option_set(command_line.options, "-p") && !is_str_in_arr((const char *const *)command_line.files, "-"))) {
        return true;
    }
    return false;
}

static t_status prepare_buffers(u_int32_t **hash_output, char **hex_hash) {
    *hash_output = ft_calloc(9, sizeof(u_int32_t));
    if (*hash_output == NULL) 
        return FAIL;

    *hex_hash = ft_calloc(257, sizeof(char));
    if (hex_hash == NULL) {
        ft_free(*hash_output);
        return FAIL;
    }
    return SUCCESS;
}

static void handle_output(t_command_line command_line, char *hex_hash, size_t working_file_index, 
                          bool implicit_stdin, u_int32_t *hash_output) {
    size_t size = is_equal(command_line.command, "sha256") == SUCCESS ? 8 : 4;
    format_hex_hash(hash_output, hex_hash, size);
    print_result(command_line, hex_hash, working_file_index, implicit_stdin);

    ft_memset((char *)hash_output, 0, 8 * sizeof(u_int32_t));
    ft_memset(hex_hash, 0, 256 * sizeof(char));
}

t_status md_commands(void (*algorithm)(u_int32_t **input_matrix, u_int32_t *hash_output), 
                     t_command_line *command_line) {

    bool implicit_stdin = implicit_stdin_read(*command_line);
    size_t total_inputs = array_size((const char *const *)command_line->files) + (size_t)implicit_stdin;

    u_int32_t *hash_output;
    char *hex_hash;

    if (prepare_buffers(&hash_output, &hex_hash) == FAIL) 
        return alloc_err_fail_return();

    size_t file_index = 0;
    char *input;
    for (size_t i = 0; i < total_inputs; i++) {

        size_t working_file_index = file_index;
        t_status read_status = read_input(command_line, &file_index, implicit_stdin, &input);
        if (input == NULL) 
            return alloc_err_fail_return();
        if (read_status == FAIL) 
            continue;
        u_int32_t **input_matrix = create_input_matrix(input, is_equal(command_line->command, "sha256"));
        ft_free(input);
        if (input_matrix == NULL) 
            return alloc_err_fail_return();

        algorithm(input_matrix, hash_output);
        free_matrix(input_matrix);

        handle_output(*command_line, hex_hash, working_file_index, implicit_stdin, hash_output);

        implicit_stdin = false;
    }
    ft_free(hash_output);
    ft_free(hex_hash);

    return SUCCESS;
}