/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:06:36 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/07 13:45:36 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PLANE_H
# define PLANE_H

# include <stdbool.h>

# define WINDOW_WIDTH   800
# define WINDOW_HEIGHT  600

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				img;
	t_instruction_set	*instruction_set;
}	t_data;

typedef struct s_sphere_collision
{
	double			closest_t;
	t_sphere_obj	*closest_sphere;
}	t_sphere_collision;

// check_sphere.c
t_sphere_collision	find_closest_sphere(t_ray ray, t_data *mlx_data);
double				check_sphere_collision(t_ray ray, t_sphere_obj *sphere);

//tracing.c
uint32_t	background_color(t_vect unit_direction);
double		check_plane_collision(t_ray ray, t_plane_obj *plane);
uint32_t	ray_color(t_ray ray, t_data *mlx_data);




# endif
