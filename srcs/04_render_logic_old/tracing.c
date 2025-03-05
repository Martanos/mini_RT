/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:07:39 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/20 13:52:07 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

uint32_t	calculate_ambient_lighting(uint32_t obj_color, t_master *master)
{
	double		ambient;
	uint32_t	amb_color;
	uint8_t		rgb[3];
	uint8_t		amb_rgb[3];
	uint8_t		final[3];

	ambient = master->amb_head.ratio;
	amb_color = master->amb_head.rgb;
	ft_convert_rgb_arr(obj_color, rgb);
	ft_convert_rgb_arr(amb_color, amb_rgb);
	final[0] = (uint8_t)(rgb[0] * ambient * (amb_rgb[0] / 255.0));
	final[1] = (uint8_t)(rgb[1] * ambient * (amb_rgb[1] / 255.0));
	final[2] = (uint8_t)(rgb[2] * ambient * (amb_rgb[2] / 255.0));
	return (ft_create_rgb(final[0], final[1], final[2]));
}

uint32_t	calculate_diffuse_lighting(t_hit_record hit, t_light *light,
		uint32_t obj_color, t_material mat)
{
	double	diff;
	double	intensity;
	uint8_t	rgb[3];
	uint8_t	light_rgb[3];
	t_vect	light_dir;

	light_dir = ft_vect_norm(ft_vect_sub(light->cord, hit.point));
	diff = fmax(ft_vect_dot(hit.normal, light_dir), 0.0);
	if (mat.diff > 0)
		intensity = light->ratio * diff * mat.diff;
	else
		intensity = light->ratio * diff;
	ft_convert_rgb_arr(obj_color, rgb);
	ft_convert_rgb_arr(light->color, light_rgb);
	rgb[0] = (uint8_t)(rgb[0] * intensity * (light_rgb[0] / 255.0));
	rgb[1] = (uint8_t)(rgb[1] * intensity * (light_rgb[1] / 255.0));
	rgb[2] = (uint8_t)(rgb[2] * intensity * (light_rgb[2] / 255.0));
	return (ft_create_rgb(rgb[0], rgb[1], rgb[2]));
}

uint32_t	background_color(t_vect unit_direction)
{
	uint8_t	rgb[3];
	double	t;

	t = (unit_direction.y + 1.0) * 0.5;
	rgb[0] = (uint8_t)((1.0 - t) * 135 + t * 25);
	rgb[1] = (uint8_t)((1.0 - t) * 206 + t * 25);
	rgb[2] = (uint8_t)((1.0 - t) * 235 + t * 112);
	return (ft_create_rgb(rgb[0], rgb[1], rgb[2]));
}

static void	add_light_contribution(t_light *light, t_intersection_info info,
		t_master *master, uint8_t final[3])
{
	t_ray		shadow_ray;
	double		light_distance;
	uint32_t	color;
	uint8_t		rgb[3];
	uint8_t		spec_rgb[3];

	light_distance = ft_vect_mag(ft_vect_sub(light->cord, info.hit.point));
	shadow_ray = calculate_shadow_ray(info.hit.point, light->cord,
			info.hit.normal);
	if (!check_shadow_intersection(shadow_ray, light_distance, master))
	{
		color = calculate_diffuse_lighting(info.hit, light, info.color,
				info.properties.mat);
		ft_convert_rgb_arr(color, rgb);
		if (info.properties.mat.spec > 0 && info.properties.mat.shin > 0)
		{
			ft_convert_rgb_arr(calc_specular(info.hit, master->cam_head.cord,
					light, info.properties.mat), spec_rgb);
			ft_clamp_rgb_values(spec_rgb, spec_rgb);
			ft_color_mixer(rgb, spec_rgb, 0.5);
		}
		ft_color_mixer(final, rgb, 0.5);
	}
}

uint32_t	ray_color(t_ray ray, t_master *master, int depth)
{
	t_intersection_info	info;
	t_light				*light;
	uint8_t				final[3];
	uint32_t			color;
	uint32_t			reflected_color;

	info = find_closest_intersection(ray, master);
	if (info.hit.t == 0)
		return (background_color(ft_vect_norm(ray.direction)));
	color = calculate_ambient_lighting(info.color, master);
	ft_convert_rgb_arr(color, final);
	light = master->light_head;
	while (light)
	{
		add_light_contribution(light, info, master, final);
		light = light->next;
	}
	if (info.properties.mat.refl > 0.0 && depth > 0)
	{
		reflected_color = calculate_reflection(info, ray, master, depth - 1);
		ft_convert_rgb_arr(reflected_color, final);
	}
	return (ft_create_rgb(final[0], final[1], final[2]));
}
