/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:06:36 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/03 15:02:48 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "mini_rt.h"
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

// check_sphere.c
t_sphere_collision		find_closest_sphere(t_ray ray, t_data *mlx_data, t_master *master);
double					check_sphere_collision(t_ray ray, t_sphere *sphere);
void					calculate_sphere_hit(t_ray ray,
							t_sphere_collision collision, t_hit_record *rec);

// check_plane.c
double					check_capped_plane_collision(t_ray ray,
							t_plane plane);
t_plane_collision		find_closest_plane(t_ray ray, t_data *mlx_data, t_master *master);
double					check_plane_collision(t_ray ray, t_plane *plane);
void					calculate_plane_hit(t_ray ray,
							t_plane_collision collision, t_hit_record *rec);

// check_cylinder.c
t_cylinder_collision	find_closest_cylinder(t_ray ray, t_data *mlx_data, t_master *master);
double					check_cylinder_collision(t_ray ray,
							t_cylinder *cylinder);
void					calculate_cylinder_hit(t_ray ray,
							t_cylinder_collision collision, t_hit_record *rec);

// check_cone.c
t_cone_collision		find_closest_cone(t_ray ray, t_data *mlx_data, t_master *master);
double					check_cone_collision(t_ray ray, t_cone *cone);
void					calculate_cone_hit(t_ray ray,
							t_cone_collision collision, t_hit_record *rec);

// tracing.c
uint32_t				background_color(t_vect unit_direction);
uint32_t				ray_color(t_ray ray, t_data *mlx_data, t_master *master);

#endif
