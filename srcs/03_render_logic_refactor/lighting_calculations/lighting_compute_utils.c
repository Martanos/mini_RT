/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_compute_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:31:25 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 11:23:09 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * Check if a point is in shadow by casting a ray to the light source
 * Returns true if the point is in shadow, false otherwise
 */
bool	ft_is_in_shadow(t_scene **scene, t_light *light)
{
	ft_memset(&(*scene)->shadow_ray, 0, sizeof(t_ray));
	ft_memset(&(*scene)->shadow_hit, 0, sizeof(t_hit));
	(*scene)->shadow_ray.origin = ft_vect_add((*scene)->hit.point,
			ft_vect_mul_all((*scene)->hit.normal, EPSILON));
	(*scene)->shadow_ray.direction = ft_vect_norm(ft_vect_sub(light->cord,
				(*scene)->hit.point));
	(*scene)->shadow_ray.t_min = EPSILON;
	(*scene)->shadow_ray.t_max = ft_vect_len(ft_vect_sub(light->cord,
				(*scene)->hit.point));
	(*scene)->shadow_hit.t = INFINITY;
	if (ft_intersect_main(scene))
		return (true);
	return (false);
}

/**
 * Calculate specular highlight using Phong reflection model
 */
t_vect	ft_calculate_specular(t_ray *ray, t_hit *hit, t_light *light,
		t_vect light_dir)
{
	t_vect	view_dir;
	t_vect	reflect_dir;
	double	spec_factor;
	t_vect	light_color;

	reflect_dir = ft_vect_sub(ft_vect_mul_all(hit->normal, 2.0
				* ft_vect_dot(hit->normal, light_dir)), light_dir);
	view_dir = ft_vect_norm(ft_vect_sub(ray->origin, hit->point));
	spec_factor = pow(fmax(0.0, ft_vect_dot(reflect_dir, view_dir)),
			hit->object->mat.shin);
	light_color = ft_rgb_to_vect(light->rgb);
	return (ft_vect_mul_all(light_color, spec_factor * hit->object->mat.spec
			* light->ratio));
}

uint32_t	ft_combine_colors(uint32_t color1, t_vect color2)
{
	t_vect	combined;

	combined = ft_vect_add(ft_rgb_to_vect(color1), color2);
	return (ft_vect_to_rgb(combined));
}
