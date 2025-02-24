/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:15:49 by vvalet            #+#    #+#             */
/*   Updated: 2023/11/08 12:01:47 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "miniRT_objects.h"
# include "miniRT_key_hooks.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <mlx.h>

# define VERIFY 0
# define CREATE 1
# define SUM 1
# define DIFF -1
# define Y_RES 1080
# define X_RES 1920
# define BACKGROUND_COLOR 531511
# define TEXT_COLOR 11861940
# define TRANSLATE_FACTOR 1
# define ROTATE_FACTOR 15
# define RESIZE_FACTOR 1

# define CAMERA_FORMAT "bad camera format: \
C position[x,y,z] orientation[x,y,z] fov\n\
position: decimals, orientation: decimals in range [-1,1], \
fov: integer in range [1, 179]\n"
# define AMBIENT_LIGHTING_FORMAT "bad ambient lighting format: \
A brightness color[r,g,b]\n\
brightness: decimal in range [0,1], color: integers in range [0,255]\n"
# define SPOT_LIGHTING_FORMAT "bad spot lighting format: \
L position[x,y,z] brightness color[r,g,b]\n\
position: decimals, brightness: decimal in range [0,1], \
color: integers in range [0,255]\n"
# define SPHERE_FORMAT "bad sphere format: \
sp position[x,y,z] diameter color[r,g,b]\n\
position: decimals, diameter: positive integer, \
color: integers in range [0,255]\n"
# define PLANE_FORMAT "bad plane format: \
pl position[x,y,z] orientation[x,y,z] color[r,g,b]\n\
position: decimals, orientation: decimals in range [-1,1], \
color: integers in range [0,255]\n"
# define CYLINDER_FORMAT "bad cylinder format: \
cy position[x,y,z] orientation[x,y,z] diameter height color[r,g,b]\n\
position: decimals, orientation: decimals in range [-1,1], \
diameter: positive integer, height: positive integer, \
color: integers in range [0,255]\n"

enum {
	CAMERA,
	AMBIENT_LIGHTING,
	SPOT_LIGHTING,
	SPHERE,
	PLANE,
	CYLINDER
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

/* Parsing */
void			file_verify(char *file);
void			file_parse(char *file, t_scene *scene);

/* Parsing: errors */
int				print_error(const char *str);
void			parsing_error(int fd, char *line, t_scene *scene);
void			clear_scene(t_scene *scene);

/* Parsing: objects */
void			choose_fct(int (**fct)(char*, t_scene*), char *line, int type);
int				verify_cam(char *line, t_scene *scene);
int				verify_al(char *line, t_scene *scene);
int				verify_sl(char *line, t_scene *scene);
int				verify_sphere(char *line, t_scene *scene);
int				verify_plane(char *line, t_scene *scene);
int				verify_cylinder(char *line, t_scene *scene);
int				create_cam(char *line, t_scene *scene);
int				create_al(char *line, t_scene *scene);
int				create_sl(char *line, t_scene *scene);
int				create_sphere(char *line, t_scene *scene);
int				create_plane(char *line, t_scene *scene);
int				create_cylinder(char *line, t_scene *scene);

/* Parsing: utils */
void			ft_ftoa(double n, char buffer[400]);
double			ft_atof(const char *str);
int				ft_next_char(char *str, char c);
int				ft_skip_nbrs(char *str);
int				int_overflow(char *str);
char			*is_whole_number(char *str);
char			*is_fractional(char *str);
char			*is_whole_number_range(char *str, int min, int max);
char			*is_fract_range(char *str, double min, double max);
char			*is_coordinates(char *str);
char			*is_vector(char *str);
char			*is_color(char *str);
int				add_coordinates(char *line, t_coordinates *coordinates);
int				add_norm_vector(char *line, t_coordinates *vector);
int				add_color(char *line, t_color *color);

/* Color calculation */
int				find_color(t_scene *scene, int x, int y);
void			find_point_seen(t_scene *scene, t_color_finder *data);
void			calculate_color(t_scene *scene, t_color_finder *data);
int				has_light(t_scene *scene, t_color_finder *data);
int				on_object(t_color_finder *data, t_list *lst, int o_type);

/* Color management */
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
t_color			make_color_trgb(int trgb);
t_color			make_color(unsigned int red, 
					unsigned int green, unsigned int blue);

/* Object intersect checks */
double			*quadratic_solution(double x[2], double abc[3]);
void			update_data_info(void *obj_ptr, t_color_finder *data,
					double *t_value, double new_t);
void			check_sphere(t_sphere *sphere,
					t_color_finder *data, double *t_value);
void			check_plane(t_plane *plane, t_color_finder *data,
					double *t_value);
double			sign_of(double n);
int				is_on_cyl(t_coordinates point, t_cylinder *cyl);
int				inside_cyl(t_coordinates point, t_cylinder *cyl);
void			check_spot(t_scene *scene);

/* MLX */
void			init_window(t_mlx *mlx);
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void			check_camera_inside_object(t_scene *scene);
void			check_light_inside_object(t_scene *scene);
void			update_cylinders(t_scene *scene);
void			update_image(t_mlx *mlx);

/* Event management */
int				key_hooks(int keycode, t_mlx *mlx);
int				mclose(t_mlx *mlx);

/* vector math */
t_coordinates	cross_product(t_coordinates v1, t_coordinates v2);
double			dot_poduct(t_coordinates v1, t_coordinates v2);
double			squared_norm(t_coordinates v);
t_coordinates	normalize_vector(t_coordinates v);
t_coordinates	sum_diff_vector(t_coordinates v1, t_coordinates v2, int sum);
t_coordinates	mult_vector(double a, t_coordinates v);
void			check_plane(t_plane *plane, t_color_finder *data,
					double *t_value);
void			check_cylinder(t_cylinder *cylinder, t_color_finder *data,
					double *t_value);
void			check_sphere(t_sphere *sphere, t_color_finder *data,
					double *t_value);
int				almosteq(double a, double b);
double			ft_dabs(double a);

/* Objects manipulation */
void			display_infos(t_mlx *mlx);
void			select_object(int keycode, t_mlx *mlx);
void			translate(t_mlx *mlx, int sign, char direction);
void			rotate_x(t_mlx *mlx, int sign);
void			rotate_y(t_mlx *mlx, int sign);
void			rotate_z(t_mlx *mlx, int sign);
void			roll(t_camera *cam, double angle, char axis);
void			rotation_x(t_coordinates *v, double angle);
void			rotation_y(t_coordinates *v, double angle);
void			rotation_z(t_coordinates *v, double angle);
void			resize_diameter(t_mlx *mlx, int sign);
void			resize_height(t_mlx *mlx, int sign);

#endif
