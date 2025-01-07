/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:07:39 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/07 16:49:55 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "plane.h"

uint32_t	background_color(t_vect unit_direction)
{
	double t = unit_direction.y;  // Positive y gives higher t value (blue) at top
	t = (t + 1.0) * 0.5;  // Map to [0,1]
	
	// Extract RGB components from WHITE (0xFFFFFFFF)
	uint8_t start_r = 0xFF;
	uint8_t start_g = 0xFF;
	uint8_t start_b = 0xFF;
	
	// Extract RGB components from BLUE (0xFF0000FF)
	uint8_t end_r = 0x00;
	uint8_t end_g = 0x00;
	uint8_t end_b = 0xFF;
	
	// Interpolate each component
	uint8_t r = (uint8_t)((1.0 - t) * start_r + t * end_r);
	uint8_t g = (uint8_t)((1.0 - t) * start_g + t * end_g);
	uint8_t b = (uint8_t)((1.0 - t) * start_b + t * end_b);
	
	// Combine back into 32-bit color (0xFF for alpha channel)
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}

uint32_t	ray_color(t_ray ray, t_data *mlx_data)
{
	t_sphere_collision sphere_collision;
	t_plane_collision plane_collision;
	t_vect hit_point;
	t_vect normal;
	uint8_t r, g, b;
	uint32_t obj_color;
	double shade;

	sphere_collision = find_closest_sphere(ray, mlx_data);
	plane_collision = find_closest_plane(ray, mlx_data);

	// Choose closest intersection between sphere and plane
	if (sphere_collision.closest_sphere && 
		(!plane_collision.closest_plane || sphere_collision.closest_t < plane_collision.closest_t))
	{
		hit_point = vect_add(ray.origin, vect_multiply(ray.direction, sphere_collision.closest_t));
		normal = vect_normalize(vect_sub(hit_point, sphere_collision.closest_sphere->sphere_pos));
		obj_color = sphere_collision.closest_sphere->sphere_rgb;
	}
	else if (plane_collision.closest_plane)
	{
		hit_point = vect_add(ray.origin, vect_multiply(ray.direction, plane_collision.closest_t));
		normal = plane_collision.closest_plane->plane_normal;
		obj_color = plane_collision.closest_plane->plane_rgb;
	}
	else
	{
		// Return background color if no collision
		t_vect unit_direction = vect_normalize(ray.direction);
		return (background_color(unit_direction));
	}

	// Extract RGB components from object's color
	r = (uint8_t)((obj_color >> 16) & 0xFF);
	g = (uint8_t)((obj_color >> 8) & 0xFF);
	b = (uint8_t)(obj_color & 0xFF);
	
	// Apply shading based on normal direction (dot product with up vector)
	shade = 0.5 * (1.0 + vect_dot(normal, (t_vect){0, 1, 0}));
	r = (uint8_t)(r * shade);
	g = (uint8_t)(g * shade);
	b = (uint8_t)(b * shade);
	
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}
