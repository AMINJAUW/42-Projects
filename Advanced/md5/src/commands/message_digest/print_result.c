/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:46:17 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/09 14:03:36 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char *to_uppercase(char *str, char *dest) {
    for (size_t i = 0; str[i]; i ++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            dest[i] = str[i] - 'a' + 'A';
        }
        else
            dest[i] = str[i];
    }
    return dest;
}

static void print_hash_and_file(char *hex_hash, char *file, bool is_file_str) {
    write_str(hex_hash);
    write_str(" ");
    if (is_file_str) {
        write_str("\"");
        write_str(file);
        write_str("\"");
    } else {
        write_str(file);
    }
    write_str("\n");
}

static void print_hash_with_prefix(char *command, char *hex_hash, char *file, bool is_file_str, bool implicit_stdin) {
    if (!is_equal("stdin", file)) {
        char uppercase[50] = {0};
        write_str(to_uppercase(command, uppercase));
        write_str(" ");
    }
    write_str("(");
    if (is_file_str) {
        write_str("\"");
        write_str(file);
        write_str("\"");
    } else {
        write_str(file);
    }
    write_str(")");
    if (!implicit_stdin)
        write_str(" ");
    write_str("= ");
    write_str(hex_hash);
    write_str("\n");
}

static void handle_p_option(t_command_line command_line, char *hex_hash, size_t *input_str_index) {
    if (is_option_set(command_line.options, "-q")) {
        for (size_t i = 0; command_line.input_str[*input_str_index][i]; i++) {
            if (command_line.input_str[*input_str_index][i] == '\n' && command_line.input_str[*input_str_index][i + 1] == '\0')
                break;
            write(1, &(command_line.input_str[*input_str_index][i]), 1);
        }
        write_str("\n");
    } else {
        write_str("(\"");
        for (size_t i = 0; command_line.input_str[*input_str_index][i]; i++) {
            if (command_line.input_str[*input_str_index][i] == '\n' && command_line.input_str[*input_str_index][i + 1] == '\0')
                break;
            write(1, &(command_line.input_str[*input_str_index][i]), 1);
        }
        write_str("\")= ");
    }
    write_str(hex_hash);
    write_str("\n");
    (*input_str_index)++;
}

void print_result(t_command_line command_line, char *hex_hash, size_t file_index, bool implicit_stdin) {
    char *file = "stdin";
    static size_t input_str_index = 0;

    if ((implicit_stdin || is_equal(command_line.files[file_index], "-")) &&
        is_option_set(command_line.options, "-p")) {
        handle_p_option(command_line, hex_hash, &input_str_index);
        return;
    }

    if (!implicit_stdin) {
        file = command_line.files[file_index];
    }
    
    bool is_file_str = (file_index == 0 && is_option_set(command_line.options, "-s"));
    
    if (is_option_set(command_line.options, "-q")) {
        write_str(hex_hash);
        write_str("\n");
    } else if (is_option_set(command_line.options, "-r")) {
        print_hash_and_file(hex_hash, file, is_file_str);
    } else {
        print_hash_with_prefix(command_line.command, hex_hash, file, is_file_str, implicit_stdin);
    }
}