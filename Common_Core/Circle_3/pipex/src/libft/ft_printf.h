/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:41:33 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/25 10:57:29 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define LOWHEX "0123456789abcdef"
# define HIGHHEX "0123456789ABCDEF"
# define NULLP "(null)"

typedef struct s_print
{
	va_list	args;
	int		width;
	int		precision;
	int		zero;
	int		point;
	int		dash;
	int		printed;
	int		plus;
	int		hash;
	int		space;
	int		neg;
	int		wrong;
}	t_print;

int		print_format(t_print *print_info, char *format, int i);
int		ft_printf(const char *format, ...);
char	*make_patted_num(t_print *tab, char *s_num, long long num);
int		free_all(t_print *tab, int string, ...);

int		print_front_sign(t_print *tab, int after, char *s_num, int is_int);
int		print_hash(t_print *tab, char *s_num, char x);
char	*base_change(unsigned long long num, char *base);
int		base_number_size(unsigned long long num, int base_len);

int		ft_print_char(t_print *tab);
int		ft_print_string(t_print *tab);
int		ft_print_address(t_print *tab);
int		ft_print_int(t_print *tab);
int		ft_print_uint(t_print *tab);
int		ft_print_lowhex(t_print *tab);
int		ft_print_highhex(t_print *tab);
int		ft_print_percent(t_print *tab);

#endif