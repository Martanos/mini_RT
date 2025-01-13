/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:06:36 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/13 13:41:55 by seayeo           ###   ########.fr       */
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

typedef struct s_plane_collision
{
	double			closest_t;
	t_plane_obj		*closest_plane;
}	t_plane_collision;

typedef struct s_cylinder_collision
{
	double			closest_t;
	t_cylinder_obj	*closest_cylinder;
}	t_cylinder_collision;

// check_sphere.c
t_sphere_collision	find_closest_sphere(t_ray ray, t_data *mlx_data);
double				check_sphere_collision(t_ray ray, t_sphere_obj *sphere);
void	calculate_sphere_hit(t_ray ray, t_sphere_collision collision, t_hit_record *rec);

// check_plane.c
double	check_capped_plane_collision(t_ray ray, t_capped_plane plane);
t_plane_collision	find_closest_plane(t_ray ray, t_data *mlx_data);
double				check_plane_collision(t_ray ray, t_plane_obj *plane);
void	calculate_plane_hit(t_ray ray, t_plane_collision collision, t_hit_record *rec);

// check_cylinder.c
t_cylinder_collision	find_closest_cylinder(t_ray ray, t_data *mlx_data);
double				check_cylinder_collision(t_ray ray, t_cylinder_obj *cylinder);
void	calculate_cylinder_hit(t_ray ray, t_cylinder_collision collision, t_hit_record *rec);

//tracing.c
uint32_t			background_color(t_vect unit_direction);
uint32_t			ray_color(t_ray ray, t_data *mlx_data);




# endif