/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:07:39 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/07 13:57:18 by seayeo           ###   ########.fr       */
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

double	check_plane_collision(t_ray ray, t_plane_obj *plane)
{
	double	denom;
	t_vect	p0l0;
	double	t;

	denom = vect_dot(plane->plane_normal, ray.direction);
	if (fabs(denom) < 1e-6)  // Ray is parallel to plane
		return (-1.0);

	p0l0 = vect_sub(plane->plane_pos, ray.origin);
	t = vect_dot(p0l0, plane->plane_normal) / denom;

	if (t < 0.0)  // Plane is behind ray
		return (-1.0);
	return (t);
}

uint32_t	ray_color(t_ray ray, t_data *mlx_data)
{
	t_sphere_collision collision;
	t_vect hit_point;
	t_vect normal;
	uint8_t r, g, b;

	collision = find_closest_sphere(ray, mlx_data);
	if (collision.closest_sphere)
	{
		// Calculate hit point
		hit_point = vect_add(ray.origin, vect_multiply(ray.direction, collision.closest_t));
		
		// Calculate normal vector
		normal = vect_normalize(vect_sub(hit_point, collision.closest_sphere->sphere_pos));
		
		// Map normal components from [-1,1] to [0,1] for color
		r = (uint8_t)((normal.x + 1.0) * 127.5);
		g = (uint8_t)((normal.y + 1.0) * 127.5);
		b = (uint8_t)((normal.z + 1.0) * 127.5);
		
		return (0xFF000000 | (r << 16) | (g << 8) | b);
	}

	// Return background color if no collision
	t_vect unit_direction = vect_normalize(ray.direction);
	return (background_color(unit_direction));
}
