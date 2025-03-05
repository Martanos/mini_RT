/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:28:28 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 11:32:55 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * Calculate reflection direction vector
 */
t_vect	ft_calculate_reflection_direction(t_vect incident, t_vect normal)
{
	double	dot;
	t_vect	scaled_normal;

	dot = ft_vect_dot(incident, normal);
	scaled_normal = ft_vect_mul_all(normal, 2 * dot);
	return (ft_vect_sub(incident, scaled_normal));
}

/**
 * Initialize a reflection ray from a hit point
 */
void	ft_setup_reflection_ray(t_ray *original_ray, t_hit *hit,
		t_ray *reflect_ray)
{
	t_vect	reflect_dir;

	// Calculate reflection direction
	reflect_dir = ft_calculate_reflection_direction(original_ray->direction,
			hit->normal);
	// Set up the reflection ray
	reflect_ray->origin = ft_vect_add(hit->point, ft_vect_mul_all(hit->normal,
				EPSILON));
	reflect_ray->direction = ft_vect_norm(reflect_dir);
	reflect_ray->t_min = EPSILON;
	reflect_ray->t_max = INFINITY;
	reflect_ray->depth = original_ray->depth + 1;
}

/**
 * Calculate lighting for a reflection hit point
 */
void	ft_calculate_reflection_color(t_scene **scene, t_ray *reflect_ray,
		t_hit *reflect_hit, t_vect *reflect_color)
{
	t_amb	amb;
	t_vect	base_reflect_color;
	t_vect	ambient_color;

	// Get base color of reflected object
	ft_get_base_colour(reflect_hit);
	// Calculate lighting for reflected point
	ft_calculate_surface_normal(reflect_hit);
	// Add ambient light
	amb = (*scene)->amb_data;
	base_reflect_color = ft_rgb_to_vect(reflect_hit->pixel_color);
	ambient_color = ft_rgb_to_vect(amb.rgb);
	*reflect_color = ft_vect_mul(base_reflect_color,
			ft_vect_mul_all(ambient_color, amb.ratio));
	// Add diffuse and specular lighting
	ft_apply_diffuse_and_specular(*scene, reflect_ray, reflect_hit,
		reflect_color);
}

/**
 * Blend original color with reflection color based on reflection coefficient
 */
void	ft_blend_reflection(t_hit *hit, t_vect *original_color,
		t_vect reflection_color)
{
	double	refl;

	refl = hit->object->mat.refl;
	// Blend original color with reflection color
	*original_color = ft_vect_add(ft_vect_mul_all(*original_color, 1.0 - refl),
			ft_vect_mul_all(reflection_color, refl));
}

/**
 * Main function for calculating and tracing reflection rays
 */
void	ft_add_reflection(t_scene **scene, t_ray *ray, t_hit *hit,
		t_vect *color)
{
	t_ray	reflect_ray;
	t_hit	reflect_hit;
	t_vect	reflect_color;

	if (ray->depth >= MAX_RECURSION_DEPTH || hit->object->mat.refl <= 0)
		return ;
	reflect_color = ft_vect_create(0, 0, 0);
	ft_setup_reflection_ray(ray, hit, &reflect_ray);
	reflect_hit.t = INFINITY;
	if (ft_find_closest_intersection(*scene, &reflect_ray, &reflect_hit))
	{
		// Calculate color at reflection hit point
		ft_calculate_reflection_color(*scene, &reflect_ray, &reflect_hit,
			&reflect_color);
		// Recursively add further reflections
		ft_add_reflection(*scene, &reflect_ray, &reflect_hit, &reflect_color);
		// Blend reflection color with original color
		ft_blend_reflection(hit, color, reflect_color);
	}
}
