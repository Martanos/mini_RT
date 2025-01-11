/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:07:39 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/11 15:57:53 by seayeo           ###   ########.fr       */
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
	t_cylinder_collision cylinder_collision;
	t_hit_record hit_record;
	uint8_t r, g, b;
	uint32_t obj_color;

	sphere_collision = find_closest_sphere(ray, mlx_data);
	plane_collision = find_closest_plane(ray, mlx_data);
	cylinder_collision = find_closest_cylinder(ray, mlx_data);

	// Choose closest intersection between sphere, plane, and cylinder
	if (sphere_collision.closest_sphere && 
		(!plane_collision.closest_plane || sphere_collision.closest_t < plane_collision.closest_t) &&
		(!cylinder_collision.closest_cylinder || sphere_collision.closest_t < cylinder_collision.closest_t))
	{
		calculate_sphere_hit(ray, sphere_collision, &hit_record);
		obj_color = sphere_collision.closest_sphere->sphere_rgb;
	}
	else if (plane_collision.closest_plane &&
		(!cylinder_collision.closest_cylinder || plane_collision.closest_t < cylinder_collision.closest_t))
	{
		calculate_plane_hit(ray, plane_collision, &hit_record);
		obj_color = plane_collision.closest_plane->plane_rgb;
	}
	else if (cylinder_collision.closest_cylinder)
	{
		calculate_cylinder_hit(ray, cylinder_collision, &hit_record);
		obj_color = cylinder_collision.closest_cylinder->cylinder_rgb;
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
	
	// Apply ambient lighting
	double ambient = mlx_data->instruction_set->amb_light_ratio;
	uint32_t amb_color = mlx_data->instruction_set->amb_light_rgb;
	uint8_t amb_r = (uint8_t)((amb_color >> 16) & 0xFF);
	uint8_t amb_g = (uint8_t)((amb_color >> 8) & 0xFF);
	uint8_t amb_b = (uint8_t)(amb_color & 0xFF);

	// Initialize with ambient lighting
	double final_r = r * ambient * (amb_r / 255.0);
	double final_g = g * ambient * (amb_g / 255.0);
	double final_b = b * ambient * (amb_b / 255.0);
	
	// Add contribution from each light source
	int i = 0;
	while (mlx_data->instruction_set->light_obj_list[i])
	{
		t_light_obj *light = mlx_data->instruction_set->light_obj_list[i];
		
		// Calculate direction and distance to light
		t_vect light_dir = vect_sub(light->light_pos, hit_record.point);
		double light_distance = vect_magnitude(light_dir);
		light_dir = vect_normalize(light_dir);

		// Create shadow ray (offset origin slightly along normal to prevent self-intersection)
		t_ray shadow_ray;
		t_vect offset = vect_multiply(hit_record.normal, 0.001); // Small offset to prevent self-intersection
		shadow_ray.origin = vect_add(hit_record.point, offset);
		shadow_ray.direction = light_dir;

		// Check for shadows by testing if any object blocks the path to light
		t_sphere_collision shadow_sphere = find_closest_sphere(shadow_ray, mlx_data);
		t_plane_collision shadow_plane = find_closest_plane(shadow_ray, mlx_data);
		t_cylinder_collision shadow_cylinder = find_closest_cylinder(shadow_ray, mlx_data);

		// Skip light contribution if point is in shadow (only if intersection is closer than light)
		if ((shadow_sphere.closest_sphere && shadow_sphere.closest_t < light_distance) ||
			(shadow_plane.closest_plane && shadow_plane.closest_t > 0.001 && shadow_plane.closest_t < light_distance)
			|| (shadow_cylinder.closest_cylinder && shadow_cylinder.closest_t < light_distance))
		{
			i++;
			continue;
		}

		// Calculate diffuse lighting
		double diff = fmax(vect_dot(hit_record.normal, light_dir), 0.0);
		double intensity = light->light_intensity * diff;

		// Get light color
		uint8_t light_r = (uint8_t)((light->light_rgb >> 16) & 0xFF);
		uint8_t light_g = (uint8_t)((light->light_rgb >> 8) & 0xFF);
		uint8_t light_b = (uint8_t)(light->light_rgb & 0xFF);

		// Add light contribution (only if not in shadow)
		final_r += r * intensity * (light_r / 255.0);
		final_g += g * intensity * (light_g / 255.0);
		final_b += b * intensity * (light_b / 255.0);

		i++;
	}

	// Clamp values between 0 and 255
	r = (uint8_t)fmin(fmax(final_r, 0), 255);
	g = (uint8_t)fmin(fmax(final_g, 0), 255);
	b = (uint8_t)fmin(fmax(final_b, 0), 255);
	
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}
