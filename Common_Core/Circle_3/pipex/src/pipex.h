/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:22:31 by aminjauw          #+#    #+#             */
/*   Updated: 2025/02/24 16:14:47 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <fcntl.h>

# define FALSE 0
# define TRUE 1

/*--------------Parsing-----------------*/
int		malloc_error(void *addr, int nbr, ...);
int		arr_len(char **arr);
char	**make_paths(char **env);
char	***make_array(char **path, char *av_str);
int		free_arr(int dim, void **arr);
int		free_a(int number, ...);
char	**arg_split(char *av_str);
int		init_to_zero(int n, ...);
int		is_sep(char c, char sep);
int		count_char(char *str, char c);
int		close_mult(int n, ...);
#endif