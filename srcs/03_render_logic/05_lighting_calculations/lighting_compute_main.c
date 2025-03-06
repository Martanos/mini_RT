/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_compute_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:06:19 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 17:08:48 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * Apply lighting calculations to the hit point
 * Updates the color of the hit point with lighting effects
 */
static void	ft_apply_lighting(t_scene **scene, t_ray *ray, t_hit *hit,
		t_vect *color)
{
	t_light	*light;
	t_vect	light_dir;
	double	diffuse_factor;
	t_vect	diffuse;
	t_vect	color;
	t_vect	specular;

	light = (*scene)->light_data;
	while (light)
	{
		light_dir = ft_vect_norm(ft_vect_sub(light->cord, hit->point));
		if (!ft_is_in_shadow(scene, light))
		{
			diffuse_factor = fmax(0.0, ft_vect_dot(hit->normal, light_dir));
			diffuse = ft_vect_mul_all(ft_rgb_to_vect(light->rgb), diffuse_factor
					* light->ratio);
			*color = ft_vect_add(*color, diffuse);
			if (hit->object->mat.enabled && hit->object->mat.spec > 0)
				*color = ft_vect_add(*color, ft_calculate_specular(ray, hit,
							light, light_dir));
		}
		light = light->next;
	}
}

void	ft_calculate_lighting(t_scene **scene, t_z_buffer **z_buffer)
{
	ft_add_ambient_to_base(scene, &(*z_buffer)->cam_hit);
	ft_apply_lighting(scene, &(*z_buffer)->cam_ray, &(*z_buffer)->cam_hit,
		&color);
}
