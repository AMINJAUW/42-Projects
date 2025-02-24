/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:41:32 by aminjauw          #+#    #+#             */
/*   Updated: 2023/05/09 10:53:35 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define A 1
# define B 0
# define TRUE 1
# define FALSE 0

typedef struct s_arr
{
	int	*a;
	int	len_a;
	int	max_a;
	int	min_a;
	int	*b;
	int	len_b;
	int	max_b;
	int	min_b;
}		t_arr;

/*---Libft functions---*/
int		ft_printf(const char *format, ...);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
char	**ft_split(char const *s, char c);

/*---Init & free functions---*/
int		ft_free_a(int number, ...);
int		ft_init_struct(int argc, char **argv, t_arr *tabs);
int		ft_init_struct_str(int argc, char **argv, t_arr *tabs);
int		ft_only_zero(char *str);
int		init_max_min(t_arr *tabs);
int		ft_new_max(t_arr *tabs, int a, int max);
int		ft_new_min(t_arr *tabs, int a, int min);

/*---Move functions---*/
void	ft_p(t_arr *tabs, int a);
void	ft_r(t_arr *tabs, int a);
void	ft_rr(t_arr *tabs);
void	ft_rrab(t_arr *tabs, int a);
void	ft_rrr(t_arr *tabs);
void	ft_s(t_arr *tabs, int a);
void	ft_ss(t_arr *tabs);

/*---Basic functions---*/
int		ft_same_sign(int a, int b);
int		ft_abs(int i);
int		ft_sign(int i);
int		ft_is_sorted(int *tab, int len, int increase);
int		ft_find_max(t_arr *tabs, int a);
int		ft_find_min(t_arr *tabs, int a);
int		ft_rot_sort(t_arr *tabs, int a, int increasing);

/*---Big functions---*/
int		ft_calculate(t_arr *tabs);
void	ft_arange_one_more(t_arr *tabs, int a);
int		ft_should_be(t_arr *tabs, int number, int a);
void	ft_sort_small(t_arr *tabs, int nb);
int		ft_sort_big(t_arr *tabs);
void	ft_put_best_on_top(t_arr *tabs, int **pos_moves);
void	ft_fill_tab(t_arr *tabs, int **pos_moves);
int		process(int argc, char **argv, int bonus);

#endif
