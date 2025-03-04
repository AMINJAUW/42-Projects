/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:34:07 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/08 22:55:07 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void print_invalid_command(const t_command_line *command_line, const t_hashtable *functions) {
	write_str("ft_ssl: Error: \'");
	write_str(command_line->command);
	write_str("\' is an invalid command.\n\n");
	write_str("Commands:\n");
	t_hashtable_iterator it = ht_iterator(functions);
	while (ht_next(&it)) {
		write_str(it.key);
		write_str("\n");
		functions++;
	}
	write_str("\n");
	write_str("Flags:\n");
	it = ht_iterator(command_line->options);
	while (ht_next(&it)) {
		write_str(it.key);
		write_str(" ");
	}
	write_str("\n");
}

//Print Error in the stdin and return NULL
void *alloc_err() {
    write_str("ft_ssl: Error: Allocation error ");
    return NULL;
}

//Print Error in the stdin and return FAIL
t_status alloc_err_fail_return() {
    write_str("ft_ssl: Error: Allocation error ");
    return FAIL;
}

void print_file_error(const char *program, const char *command, const char * file_name, char *strerror) {
	write_str(program);
	write_str(": ");
	write_str(command);
	write_str(": ");
	write_str(file_name);
	write_str(": ");
	write_str(strerror);
	write_str("\n");
}