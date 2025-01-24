/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:06:36 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/21 18:56:59 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "mini_rt.h"
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

// check_sphere.c
t_sphere_collision		find_closest_sphere(t_ray ray, t_data *mlx_data);
double					check_sphere_collision(t_ray ray, t_sphere_obj *sphere);
void					calculate_sphere_hit(t_ray ray,
							t_sphere_collision collision, t_hit_record *rec);

// check_plane.c
double					check_capped_plane_collision(t_ray ray,
							t_capped_plane plane);
t_plane_collision		find_closest_plane(t_ray ray, t_data *mlx_data);
double					check_plane_collision(t_ray ray, t_plane_obj *plane);
void					calculate_plane_hit(t_ray ray,
							t_plane_collision collision, t_hit_record *rec);

// check_cylinder.c
t_cylinder_collision	find_closest_cylinder(t_ray ray, t_data *mlx_data);
double					check_cylinder_collision(t_ray ray,
							t_cylinder_obj *cylinder);
void					calculate_cylinder_hit(t_ray ray,
							t_cylinder_collision collision, t_hit_record *rec);

// check_cone.c
t_cone_collision		find_closest_cone(t_ray ray, t_data *mlx_data);
double					check_cone_collision(t_ray ray, t_cone_object *cone);
void					calculate_cone_hit(t_ray ray,
							t_cone_collision collision, t_hit_record *rec);

// tracing.c
uint32_t				background_color(t_vect unit_direction);
uint32_t				ray_color(t_ray ray, t_data *mlx_data);

#endif
