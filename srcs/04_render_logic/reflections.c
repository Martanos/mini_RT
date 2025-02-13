/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:51:00 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/13 14:15:55 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

/**

	* @brief Calculates the reflected color for surfaces with a reflection coefficient
 *
 * This function:

	* 1. Checks the current recursion depth and the material's reflection coefficient.
 * 2. Computes the reflection direction using calc_reflected_ray().
 * 3. Casts a reflection ray and retrieves its color via ray_color().
 * 4. Converts both the surface color and the reflected color to RGB arrays.

	* 5. Blends the two colors based on the reflection coefficient and returns the result.
 *

	* @param info   Intersection information containing hit details and material properties
 * @param ray    The incoming ray that hit the surface
 * @param master The main structure containing scene objects and settings
 * @param depth  The remaining reflection depth
 * @return uint32_t  Returns the blended color value (in 0xRRGGBB format)
 */
uint32_t	calculate_reflection(t_intersection_info info, t_ray ray,
		t_master *master, int depth)
{
	t_ray		reflected_ray;
	t_vect		reflected_dir;
	uint32_t	reflected_color;
	uint8_t		refl_rgb[3];
	uint8_t		surface_rgb[3];

	ft_bzero(refl_rgb, sizeof(refl_rgb));
	ft_bzero(surface_rgb, sizeof(surface_rgb));
	if (depth <= 0 || info.properties.mat.refl <= 0.0)
		return (info.color);
	reflected_dir = calc_reflected_ray(ft_vect_norm(ray.direction),
			info.hit.normal);
	reflected_ray.origin = info.hit.point;
	reflected_ray.direction = reflected_dir;
	reflected_color = ray_color(reflected_ray, master, depth);
	ft_convert_rgb_arr(reflected_color, refl_rgb);
	ft_convert_rgb_arr(info.color, surface_rgb);
	surface_rgb[0] = (uint8_t)(surface_rgb[0] * (1 - info.properties.mat.refl)
			+ refl_rgb[0] * info.properties.mat.refl);
	surface_rgb[1] = (uint8_t)(surface_rgb[1] * (1 - info.properties.mat.refl)
			+ refl_rgb[1] * info.properties.mat.refl);
	surface_rgb[2] = (uint8_t)(surface_rgb[2] * (1 - info.properties.mat.refl)
			+ refl_rgb[2] * info.properties.mat.refl);
	return (ft_create_rgb(surface_rgb[0], surface_rgb[1], surface_rgb[2]));
}
