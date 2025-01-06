/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:07:39 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/06 22:02:26 by seayeo           ###   ########.fr       */
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

double	check_sphere_collision(t_ray ray, t_sphere_obj *sphere)
{
	t_vect	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vect_sub(ray.origin, sphere->sphere_pos);
	a = vect_dot(ray.direction, ray.direction);
	b = -2.0 * vect_dot(ray.direction, oc);
	c = vect_dot(oc, oc) - (sphere->sphere_diameter * sphere->sphere_diameter / 4.0);
	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (-1.0);
	return ((-b - sqrt(discriminant)) / (2.0 * a));
}

uint32_t	ray_color(t_ray ray, t_data *mlx_data)
{
	double		t;
	t_sphere_obj	*sphere;
	t_plane_obj	*plane;
	int			i;

	// Check spheres
	i = 0;
	while (mlx_data->instruction_set->sphere_obj_list[i])
	{
		sphere = mlx_data->instruction_set->sphere_obj_list[i];
		t = check_sphere_collision(ray, sphere);
		if (t > 0.0)
			return (sphere->sphere_rgb);
		i++;
	}

	// Check planes
	i = 0;
	while (mlx_data->instruction_set->plane_obj_list[i])
	{
		plane = mlx_data->instruction_set->plane_obj_list[i];
		t = check_plane_collision(ray, plane);
		if (t > 0.0)
			return (plane->plane_rgb);
		i++;
	}

	// Return background color if no collision
	t_vect unit_direction = vect_normalize(ray.direction);
	return (background_color(unit_direction));
}
