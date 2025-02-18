/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:20:19 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/18 15:16:32 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_vect	calc_reflected_ray(t_vect incident, t_vect normal)
{
	t_vect	reflect;
	double	dot;

	dot = ft_vect_dot(incident, normal);
	reflect = ft_vect_sub(incident, ft_vect_mul_all(normal, 2 * dot));
	return (reflect);
}

static double	get_specular_factor(t_vect light_dir, t_vect view_dir,
		t_vect normal, double shininess)
{
	t_vect	reflect_dir;
	double	spec;

	reflect_dir = calc_reflected_ray(ft_vect_mul_all(light_dir, -1), normal);
	spec = pow(fmax(ft_vect_dot(view_dir, reflect_dir), 0.0), shininess);
	spec = fmin(spec, 1.0);
	return (spec);
}

uint32_t	calc_specular(t_hit_record hit, t_vect cam_pos, t_light *light,
		t_material mat)
{
	t_vect	light_dir;
	t_vect	view_dir;
	uint8_t	light_rgb[3];
	uint8_t	final[3];
	double	intensity;

	light_dir = ft_vect_norm(ft_vect_sub(light->cord, hit.point));
	view_dir = ft_vect_norm(ft_vect_sub(cam_pos, hit.point));
	ft_convert_rgb_arr(light->color, light_rgb);
	intensity = fmin(light->ratio * mat.spec * get_specular_factor(light_dir,
				view_dir, hit.normal, mat.shin), 1.0);
	final[0] = intensity * (light_rgb[0]);
	final[1] = intensity * (light_rgb[1]);
	final[2] = intensity * (light_rgb[2]);
	return (ft_create_rgb(final[0], final[1], final[2]));
}
