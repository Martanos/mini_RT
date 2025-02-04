/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:25:42 by malee             #+#    #+#             */
/*   Updated: 2025/02/04 16:17:03 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "mini_rt.h"
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

typedef struct s_hit_record			t_hit_record;
typedef struct s_ray				t_ray;
typedef struct s_img				t_img;
typedef struct s_sphere_collision	t_sphere_collision;
typedef struct s_plane_collision	t_plane_collision;
typedef struct s_cylinder_collision	t_cylinder_collision;
typedef struct s_cone_collision		t_cone_collision;

// RENDER OBJECTS
typedef struct s_ray
{
	t_vect							origin;
	t_vect							direction;
}									t_ray;

typedef struct s_hit_record
{
	t_vect							point;
	t_vect							normal;
	double							t;
}									t_hit_record;

typedef struct s_sphere_collision
{
	double							closest_t;
	t_sphere						*closest_sphere;
}									t_sphere_collision;

typedef struct s_plane_collision
{
	double							closest_t;
	t_plane							*closest_plane;
}									t_plane_collision;

typedef struct s_cylinder_collision
{
	double							closest_t;
	t_cylinder						*closest_cylinder;
}									t_cylinder_collision;

typedef struct s_cone_collision
{
	double							closest_t;
	t_cone							*closest_cone;
}									t_cone_collision;

// check_sphere.c
t_sphere_collision					find_closest_sphere(t_ray ray,
										t_master *master);
double								check_sphere_collision(t_ray ray,
										t_sphere *sphere);
void								calculate_sphere_hit(t_ray ray,
										t_sphere_collision collision,
										t_hit_record *rec);

// check_plane.c
double								check_capped_plane_collision(t_ray ray,
										t_plane plane);
t_plane_collision					find_closest_plane(t_ray ray,
										t_master *master);
double								check_plane_collision(t_ray ray,
										t_plane *plane);
void								calculate_plane_hit(t_ray ray,
										t_plane_collision collision,
										t_hit_record *rec);

// check_cylinder.c
t_cylinder_collision				find_closest_cylinder(t_ray ray,
										t_master *master);
double								check_cylinder_collision(t_ray ray,
										t_cylinder *cylinder);
void								calculate_cylinder_hit(t_ray ray,
										t_cylinder_collision collision,
										t_hit_record *rec);

// check_cone.c
t_cone_collision					find_closest_cone(t_ray ray,
										t_master *master);
double								check_cone_collision(t_ray ray,
										t_cone *cone);
void								calculate_cone_hit(t_ray ray,
										t_cone_collision collision,
										t_hit_record *rec);

// tracing.c
uint32_t							background_color(t_vect unit_direction);
uint32_t							ray_color(t_ray ray, t_master *master);
// void	ft_render_scene(t_instruction_set *instruction_set);

void								my_pixel_put(t_img *img, int x, int y,
										int color);

#endif
