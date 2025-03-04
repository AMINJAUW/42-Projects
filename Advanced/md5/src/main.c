/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:18:58 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/09 13:43:36 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static bool valid_inputs(t_command_line command_line) {
	if (is_option_set(command_line.options, "-s") && command_line.files == NULL)
		return false;
	return true;
}

static t_status execute_command(t_command_line *command_line, const t_hashtable *functions) {
	if (!is_already_key(functions, command_line->command)) {
		print_invalid_command(command_line, functions);
		return FAIL;
	}

	if (valid_inputs(*command_line) == false) {
		write_str("Error: invalid inputs\n");
		return FAIL;
	}

	t_function_pointer *function_pointer = (t_function_pointer *)ht_get(functions, command_line->command);
	if (function_pointer == NULL)
		return FAIL;
	void *function = function_pointer->pointer;
	switch (function_pointer->type)
	{
	case MESSAGE_DIGEST:
		md_commands((void (*)(u_int32_t **input_matrix, u_int32_t *hash_output))function, command_line);
		break;
	
	default:
		print_invalid_command(command_line, functions); //no possible :)
		return FAIL;
		break;
	}
	return SUCCESS;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		write_str("usage: ft_ssl command [flags] [file/string]\n");
		return 1;
	}
	
	t_hashtable *commands = get_available_commands();
	if (commands == NULL)
		return 1;
	t_command_line command_line;
	if (get_command_line_struct(&command_line, argc, argv) == NULL) {
		ht_free_values(commands);
		ht_destroy(commands);
		return 1;
	}
	const int exit_code = execute_command(&command_line, commands) == FAIL;
	clear_memory(commands, command_line);
	return exit_code;	
}
