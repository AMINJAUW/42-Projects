/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:45:54 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/19 12:37:11 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static t_status read_fd(int fd, char **input) {
    char buffer[BUFFER_SIZE];
    size_t total_size = 0;
    size_t current_capacity = BUFFER_SIZE;

    *input = ft_calloc(current_capacity + 1, sizeof(char));
    if (*input == NULL) {
        return FAIL;
    }

    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {

        if (total_size + bytes_read >= current_capacity) {
            if (current_capacity >= SIZE_MAX / 2){
                ft_free(*input);
                *input = NULL;
                return FAIL; 
            }
            size_t new_capacity = current_capacity * 2;
            char *new_input = ft_calloc(new_capacity + 1, sizeof(char));
            if (new_input == NULL) {
                ft_free(*input);
                *input = NULL;
                return FAIL;
            }

            ft_memcpy(new_input, *input, total_size);
            ft_free(*input);
            *input = new_input;
            current_capacity = new_capacity;
        }

        memcpy(*input + total_size, buffer, bytes_read);
        total_size += bytes_read;
    }

    if (bytes_read == -1) {
        int err = errno;
        ft_free(*input);
        *input = strerror(err);
        return FAIL;
    }

    (*input)[total_size] = '\0';

    return SUCCESS;
}

static t_status save_stdin_input(t_command_line *command_line, char *input) {
    char **new_inputs = ft_calloc(array_size((char const* const*)command_line->input_str) + 2, sizeof(char *));
    if (new_inputs == NULL)
        return FAIL;
    size_t i = 0;
    if (command_line->input_str != NULL){
        while(command_line->input_str[i] != NULL) {
            new_inputs[i] = command_line->input_str[i];
            i++;
        }
    }
    new_inputs[i] = ft_strdup(input);
    if (new_inputs[i] == NULL) {
        ft_free(new_inputs);
        return FAIL;
    }
    if (command_line->input_str != NULL) {
        ft_free(command_line->input_str);
    }
    command_line->input_str = new_inputs;

    
    return SUCCESS;
}

static t_status read_stdin_to_input(t_command_line *command_line, size_t *file_index, bool implicit_stdin, char **input) {
    t_status read_status = FAIL;
    
    read_status = read_fd(STDIN_FILENO, input);
    
    if (read_status == FAIL && *input != NULL){
        print_file_error("ft_ssl", command_line->command, implicit_stdin ? "stdin" : "-", *input);
    } 
    if (read_status == SUCCESS && is_option_set(command_line->options, "-p")) {
        if (save_stdin_input(command_line, *input) == FAIL) {
            ft_free(*input);
            *input = NULL;
            return FAIL;
        }
    }
    if (implicit_stdin == false)
        (*file_index)++;
    return read_status;
}

static t_status read_str_to_input(t_command_line *command_line, size_t *file_index, char **input) {
    *input = ft_strdup(command_line->files[*file_index]); //checked before that there is at least a string to interpet as input string
    if (*input == NULL) {
        return FAIL;
    }
    (*file_index)++;
    return SUCCESS;
}

static t_status read_file_to_input(t_command_line *command_line, size_t file_index, char **input) {
    int fd = open(command_line->files[file_index], O_RDONLY);
    
    if (fd < 0){
        print_file_error("ft_ssl", command_line->command, command_line->files[file_index], strerror(errno));
        return FAIL;
    }
    
    t_status read_status = read_fd(fd, input);
        if (read_status == FAIL && *input != NULL) {
        print_file_error("ft_ssl", command_line->command, command_line->files[file_index], strerror(errno));
    }
    close(fd);
    return read_status;
}

t_status read_input(t_command_line *command_line, size_t *file_index, bool implicit_stdin, char **input) {
    t_status read_status = FAIL;    
    if (implicit_stdin || is_equal(command_line->files[*file_index], "-")) {
        read_status = read_stdin_to_input(command_line, file_index, implicit_stdin, input);
    } 
    else if (*file_index == 0 && is_option_set(command_line->options, "-s")) {
        read_status = read_str_to_input(command_line, file_index, input);
    }
    else {
        read_status = read_file_to_input(command_line, *file_index, input);
        (*file_index)++;
    }
    return read_status;
}