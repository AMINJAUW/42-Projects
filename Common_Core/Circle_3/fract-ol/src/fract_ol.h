/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:32:29 by aminjauw          #+#    #+#             */
/*   Updated: 2025/02/24 17:40:18 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include <math.h>
# include <stdlib.h>
# include "mlx/mlx.h"

# define TRUE -1
# define FALSE 0

# define MANDEL "mandelbrot"
# define JULIA	"julia"

# define SP "                                                        "

# ifndef MAX_ITERATION
#  define MAX_ITERATION 50
# endif

# define Y_RES 1080
# define X_RES 1920

enum{
	KEY_ESC		=	53,
	KEY_W		=	13,
	KEY_A		=	0,
	KEY_S		=	1,
	KEY_D		=	2,
	KEY_UP		=	126,
	KEY_DOWN	=	125,
	KEY_LEFT	=	123,
	KEY_RIGHT	=	124,
	KEY_R		=	15,
	KEY_Q		=	12,
	KEY_NUM_PLUS=	69,
	KEY_NUM_MIN	=	78
};

enum{
	MOUSE_LEFT			=	1,
	MOUSE_RIGHT			=	2,
	MOUSE_SCROLL_CLICK	=	3,
	MOUSE_SCROLL_UP		=	5,
	MOUSE_SCROLL_DOWN	=	4
};

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_complex
{
	float	re;
	float	im;
}	t_complex;

typedef struct s_info
{
	t_data		*mlx;
	float		scale;
	int			mandel;
	int			julia;
	t_complex	c;
	int			r;
	float		change;
	float		sat;
}	t_info;

/*----------Fractals------------*/
int			is_mandelbrot(t_complex c);
int			is_julia(t_complex z, t_complex c);
int			getfractalcolor(int iteration, int reverse, int saturation);
int			getfractalcolor_basic(int iteration, int reverse);

/*----------Complex-------------*/
t_complex	z_square(t_complex z);
float		sq_complex_mod(t_complex z);
int			ft_check_duplicate(t_complex *tab, int len, int i);
t_complex	complex_sum(t_complex z1, t_complex z2, int sum);
int			is_neg(float i);
/*----------Libft---------------*/
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_printf(char *format, ...);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
const char	*ft_tolower(char *str);
size_t		ft_strlen(const char *str);
int			ft_atoi(const char *str, int only_num);
/*----------Prototipes----------*/
int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
int			get_opposite_color(int color, int do_it);
int			update_img(t_info *info);
void		init(t_info *info);
int			other_keys(int keycode, t_info *info);

#endif