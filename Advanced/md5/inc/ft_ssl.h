/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 18:20:39 by aminjauw          #+#    #+#             */
/*   Updated: 2024/11/08 21:09:46 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OPENSSL_H
# define FT_OPENSSL_H

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h> //sterror
# include "hashtable.h"
# include "command.h"

# define BUFFER_SIZE 1024

//Main Structure

typedef struct s_command_line {
	char 			*command;
	t_hashtable 	*options;
	char			**files;
	char			**input_str;
} t_command_line;

//MD_COMMANDS
t_status md_commands(void (*algorithm)(u_int32_t **input_matrix, u_int32_t *hash_output), 
                     t_command_line *command_line);
t_status 	read_input(t_command_line *command_line, size_t *file_index, 
											bool implicit_stdin, char **input);
u_int32_t 	**create_input_matrix(char *input, bool big_endian);
char 		*format_hex_hash(u_int32_t *buffer, char *hex_hash, size_t size);
void 		print_result(t_command_line command_line, char *hex_hash, size_t i,
											bool implicit_stdin);


//Initialisation functions
t_hashtable *get_available_commands(void);
t_command_line *get_command_line_struct(
						t_command_line *command_line,int argc, char **argv);

//Utiliary functions
int 		ft_strlen(const char *str);
size_t 		array_size(char const* const* array);
void 		write_str(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
void		clear_memory(t_hashtable *commands, t_command_line command_line);
bool 		is_option_set(const t_hashtable *options, const char *key);
bool 		is_str_in_arr(const char * const *array, const char *str);
void		*ft_memcpy(void *dst, const void *src, size_t n);

//Error function
void 		*alloc_err();
t_status 	alloc_err_fail_return();
void 		print_invalid_command( const t_command_line *command_line,
									const t_hashtable *functions);
void 		print_file_error(const char *program, 
					const char *command, const char *file_name, char *strerror);
void		ft_memset(char *dst, char value, size_t size);


#endif
