/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_objects.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aminjauw <aminjauw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:25:44 by vvalet            #+#    #+#             */
/*   Updated: 2023/10/24 14:23:15 by aminjauw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_OBJECTS_H
# define MINIRT_OBJECTS_H

# include "libft.h"

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_coordinates
{
	double	x;
	double	y;
	double	z;
}	t_coordinates;

typedef struct s_ambient_lighting
{
	t_color	color;
	double	ratio;
}	t_ambient_lighting;

typedef struct s_camera
{
	t_coordinates	coordinates;
	t_coordinates	vector;
	t_coordinates	right_vector;
	t_coordinates	up_vector;
	double			screen_distance;
	int				fov;
}	t_camera;

typedef struct s_spot_lighting
{
	t_coordinates	coordinates;
	t_color			color;
	double			brightness;
	int				intersect_object;
}	t_spot_lighting;

typedef struct s_plane
{
	t_coordinates	coordinates;
	t_coordinates	vector;
	t_color			color;
}	t_plane;

typedef struct s_sphere
{
	t_coordinates	coordinates;
	double			diameter;
	t_color			color;
	int				camera_inside;
	int				with_light_inside;
}	t_sphere;

typedef struct s_cylinder
{
	t_coordinates	coordinates;
	t_coordinates	bottom_center;
	t_coordinates	vector;
	double			diameter;
	double			height;
	t_color			color;
	int				camera_inside;
	int				with_light_inside;
}	t_cylinder;

typedef struct s_scene
{
	t_camera			*camera;
	t_ambient_lighting	*ambient_lighting;
	t_spot_lighting		*spot_lighting;
	t_list				*spheres;
	t_list				*planes;
	t_list				*cylinders;
}	t_scene;

typedef struct s_color_finder
{
	t_color			color;
	t_coordinates	origin;
	t_coordinates	line_vector;
	t_coordinates	point_seen;
	void			*object_addr;
	int				saw_nothing;
	int				checking_light;
	t_coordinates	normal_vector_of_object_from_point;
	double			gamma;
}	t_color_finder;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_scene	*scene;
	void	*current_object;
	int		current_type;
	int		show_infos;
}	t_mlx;

#endif