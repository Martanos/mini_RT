/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:07:39 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/03 15:02:21 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Calculates the background color based on the unit direction vector
 * @param unit_direction The unit direction vector
 * @return uint32_t The background color
 */
uint32_t	ft_background_color(t_vect unit_direction)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	double	t;

	// Positive y gives higher t value (blue) at top
	t = (unit_direction.y + 1.0) * 0.5; // Map to [0,1]
	// Interpolate each component
	r = (uint8_t)((1.0 - t) * 0xFF + t * 0x00);
	g = (uint8_t)((1.0 - t) * 0xFF + t * 0x00);
	b = (uint8_t)((1.0 - t) * 0xFF + t * 0x00);
	// Combine back into 32-bit color (0xFF for alpha channel)
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}

uint32_t	ray_color(t_ray ray, t_data *mlx_data, t_master *master)
{
	t_sphere_collision		sphere_collision;
	t_plane_collision		plane_collision;
	t_cylinder_collision	cylinder_collision;
	t_cone_collision		cone_collision;
	t_hit_record			hit_record;
	uint32_t				obj_color;
	t_vect					unit_direction;
	double					ambient;
	uint32_t				amb_color;
	uint8_t					amb_r;
	uint8_t					amb_g;
	uint8_t					amb_b;
	double					final_r;
	double					final_g;
	double					final_b;
	int						i;
	t_light					*light;
	t_vect					light_dir;
	double					light_distance;
	t_ray					shadow_ray;
	t_sphere_collision		shadow_sphere;
	t_plane_collision		shadow_plane;
	t_cylinder_collision	shadow_cylinder;
	t_cone_collision		shadow_cone;
	double					diff;
	double					intensity;
	uint8_t					light_r;
	uint8_t					light_g;
	uint8_t					light_b;
	t_vect					offset;

	uint8_t r, g, b;
	sphere_collision = find_closest_sphere(ray, mlx_data);
	plane_collision = find_closest_plane(ray, mlx_data);
	cylinder_collision = find_closest_cylinder(ray, mlx_data);
	cone_collision = find_closest_cone(ray, mlx_data);
	// Choose closest intersection between sphere, plane, and cylinder
	if (sphere_collision.closest_sphere && (!plane_collision.closest_plane
			|| sphere_collision.closest_t < plane_collision.closest_t)
		&& (!cylinder_collision.closest_cylinder
			|| sphere_collision.closest_t < cylinder_collision.closest_t)
		&& (!cone_collision.closest_cone
			|| sphere_collision.closest_t < cone_collision.closest_t))
	{
		calculate_sphere_hit(ray, sphere_collision, &hit_record);
		obj_color = sphere_collision.closest_sphere->rgb;
	}
	else if (plane_collision.closest_plane
		&& (!cylinder_collision.closest_cylinder
			|| plane_collision.closest_t < cylinder_collision.closest_t)
		&& (!cone_collision.closest_cone
			|| plane_collision.closest_t < cone_collision.closest_t))
	{
		calculate_plane_hit(ray, plane_collision, &hit_record);
		obj_color = plane_collision.closest_plane->rgb;
	}
	else if (cylinder_collision.closest_cylinder
		&& (!cone_collision.closest_cone
			|| cylinder_collision.closest_t < cone_collision.closest_t))
	{
		calculate_cylinder_hit(ray, cylinder_collision, &hit_record);
		obj_color = cylinder_collision.closest_cylinder->rgb;
	}
	else if (cone_collision.closest_cone)
	{
		calculate_cone_hit(ray, cone_collision, &hit_record);
		obj_color = cone_collision.closest_cone->rgb;
	}
	else
	{
		// Return background color if no collision
		unit_direction = vect_normalize(ray.direction);
		return (ft_background_color(unit_direction));
	}
	// Extract RGB components from object's color
	r = (uint8_t)((obj_color >> 16) & 0xFF);
	g = (uint8_t)((obj_color >> 8) & 0xFF);
	b = (uint8_t)(obj_color & 0xFF);
	// Apply ambient lighting
	ambient = master->amb_head->ratio;
	amb_color = master->amb_head->rgb;
	amb_r = (uint8_t)((amb_color >> 16) & 0xFF);
	amb_g = (uint8_t)((amb_color >> 8) & 0xFF);
	amb_b = (uint8_t)(amb_color & 0xFF);
	// Initialize with ambient lighting
	final_r = r * ambient * (amb_r / 255.0);
	final_g = g * ambient * (amb_g / 255.0);
	final_b = b * ambient * (amb_b / 255.0);
	// Add contribution from each light source
	i = 0;
	light = master->light_head;
	while (light)
	{
		// Calculate direction and distance to light
		light_dir = vect_sub(light->cord, hit_record.point);
		light_distance = vect_magnitude(light_dir);
		light_dir = vect_normalize(light_dir);
		// Create shadow ray (offset origin slightly along normal to prevent self-intersection)
		offset = vect_multiply(hit_record.normal, 0.001);
		// Small offset to prevent self-intersection
		shadow_ray.origin = vect_add(hit_record.point, offset);
		shadow_ray.direction = light_dir;
		// Check for shadows by testing if any object blocks the path to light
		shadow_sphere = find_closest_sphere(shadow_ray, mlx_data);
		shadow_plane = find_closest_plane(shadow_ray, mlx_data);
		shadow_cylinder = find_closest_cylinder(shadow_ray, mlx_data);
		shadow_cone = find_closest_cone(shadow_ray, mlx_data);
		// Skip light contribution if point is in shadow (only if intersection is closer than light)
		if ((shadow_sphere.closest_sphere
				&& shadow_sphere.closest_t < light_distance)
			|| (shadow_plane.closest_plane && shadow_plane.closest_t > 0.001
				&& shadow_plane.closest_t < light_distance)
			|| (shadow_cylinder.closest_cylinder
				&& shadow_cylinder.closest_t < light_distance)
			|| (shadow_cone.closest_cone
				&& shadow_cone.closest_t < light_distance))
		{
			i++;
			continue ;
		}
		// Calculate diffuse lighting
		diff = fmax(vect_dot(hit_record.normal, light_dir), 0.0);
		intensity = light->ratio * diff;
		// Get light color
		light_r = (uint8_t)((light->rgb >> 16) & 0xFF);
		light_g = (uint8_t)((light->rgb >> 8) & 0xFF);
		light_b = (uint8_t)(light->rgb & 0xFF);
		// Add light contribution (only if not in shadow)
		final_r += r * intensity * (light_r / 255.0);
		final_g += g * intensity * (light_g / 255.0);
		final_b += b * intensity * (light_b / 255.0);
		light = light->next;
	}
	// Clamp values between 0 and 255
	r = (uint8_t)fmin(fmax(final_r, 0), 255);
	g = (uint8_t)fmin(fmax(final_g, 0), 255);
	b = (uint8_t)fmin(fmax(final_b, 0), 255);
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}
