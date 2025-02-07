/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:07:39 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/07 15:37:36 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_intersection_info	find_closest_intersection(t_ray ray, t_master *master);

uint32_t	calculate_ambient_lighting(uint32_t obj_color, t_master *master)
{
	double		ambient;
	uint32_t	amb_color;
	double		final[3];
	uint8_t		rgb[3];
	uint8_t		amb_rgb[3];

	ambient = master->amb_head.ratio;
	amb_color = master->amb_head.rgb;
	ft_convert_rgb_arr(obj_color, rgb);
	ft_convert_rgb_arr(amb_color, amb_rgb);
	final[0] = rgb[0] * ambient * (amb_rgb[0] / 255.0);
	final[1] = rgb[1] * ambient * (amb_rgb[1] / 255.0);
	final[2] = rgb[2] * ambient * (amb_rgb[2] / 255.0);
	ft_clamp_rgb_values(final, rgb);
	return (ft_create_rgb(rgb[0], rgb[1], rgb[2]));
}

t_ray	calculate_shadow_ray(t_vect hit_point, t_vect light_pos, t_vect normal)
{
	t_ray	shadow_ray;
	t_vect	offset;

	offset = ft_vect_mul_all(normal, 0.001);
	shadow_ray.origin = ft_vect_add(hit_point, offset);
	shadow_ray.direction = ft_vect_norm(ft_vect_sub(light_pos, hit_point));
	return (shadow_ray);
}

bool	check_shadow_intersection(t_ray shadow_ray, double light_distance,
	t_master *master)
{
	t_sphere_collision	shadow_sphere;
	t_plane_collision	shadow_plane;
	t_cylinder_collision	shadow_cylinder;
	t_cone_collision	shadow_cone;

	shadow_sphere = find_closest_sphere(shadow_ray, master);
	shadow_plane = find_closest_plane(shadow_ray, master);
	shadow_cylinder = find_closest_cylinder(shadow_ray, master);
	shadow_cone = find_closest_cone(shadow_ray, master);
	if (shadow_sphere.closest_sphere && shadow_sphere.closest_t < light_distance)
		return (true);
	if (shadow_plane.closest_plane && shadow_plane.closest_t > 0.001
		&& shadow_plane.closest_t < light_distance)
		return (true);
	if (shadow_cylinder.closest_cylinder
		&& shadow_cylinder.closest_t < light_distance)
		return (true);
	if (shadow_cone.closest_cone && shadow_cone.closest_t < light_distance)
		return (true);
	return (false);
}

uint32_t	calculate_light_contribution(t_hit_record hit, t_light *light,
	uint32_t obj_color)
{
	double		diff;
	double		intensity;
	uint8_t		rgb[3];
	uint8_t		light_rgb[3];
	double		final[3];
	t_vect		light_dir;

	light_dir = ft_vect_norm(ft_vect_sub(light->cord, hit.point));
	diff = fmax(ft_vect_dot(hit.normal, light_dir), 0.0);
	intensity = light->ratio * diff;
	ft_convert_rgb_arr(obj_color, rgb);
	ft_convert_rgb_arr(light->color, light_rgb);
	final[0] = rgb[0] * intensity * (light_rgb[0] / 255.0);
	final[1] = rgb[1] * intensity * (light_rgb[1] / 255.0);
	final[2] = rgb[2] * intensity * (light_rgb[2] / 255.0);
	ft_clamp_rgb_values(final, rgb);
	return (ft_create_rgb(rgb[0], rgb[1], rgb[2]));
}

t_intersection_info	find_closest_intersection(t_ray ray, t_master *master)
{
	t_intersection_info	closest;

	closest = (t_intersection_info){0};
	check_sphere_intersection(ray, master, &closest);
	check_plane_intersection(ray, master, &closest);
	check_cylinder_intersection(ray, master, &closest);
	check_cone_intersection(ray, master, &closest);
	return (closest);
}

uint32_t	background_color(t_vect unit_direction)
{
	uint8_t	rgb[3];
	double	t;

	t = (unit_direction.y + 1.0) * 0.5;
	rgb[0] = (uint8_t)((1.0 - t) * 0xFF + t * 0x00);
	rgb[1] = (uint8_t)((1.0 - t) * 0xFF + t * 0x00);
	rgb[2] = (uint8_t)((1.0 - t) * 0xFF + t * 0x00);
	return (ft_create_rgb(rgb[0], rgb[1], rgb[2]));
}

uint32_t	ray_color(t_ray ray, t_master *master)
{
	t_intersection_info	info;
	uint32_t			color;
	t_light				*light;
	t_ray				shadow_ray;
	double				light_distance;
	double				final[3];
	uint8_t				rgb[3];

	info = find_closest_intersection(ray, master);
	if (info.hit.t == 0)
		return (background_color(ft_vect_norm(ray.direction)));
	color = calculate_ambient_lighting(info.color, master);
	ft_convert_rgb_arr(color, rgb);
	final[0] = rgb[0];
	final[1] = rgb[1];
	final[2] = rgb[2];
	light = master->light_head;
	while (light)
	{
		light_distance = ft_vect_mag(ft_vect_sub(light->cord, info.hit.point));
		shadow_ray = calculate_shadow_ray(info.hit.point, light->cord, info.hit.normal);
		if (check_shadow_intersection(shadow_ray, light_distance, master))
		{
			light = light->next;
			continue ;
		}
		// specular to be added here if shadow is false
		// diffuse and specular calculated together
		// need to factor in camera position for specular
		color = calculate_light_contribution(info.hit, light, info.color);
		ft_convert_rgb_arr(color, rgb);
		final[0] += rgb[0];
		final[1] += rgb[1];
		final[2] += rgb[2];
		light = light->next;
	}
	ft_clamp_rgb_values(final, rgb);
	return (ft_create_rgb(rgb[0], rgb[1], rgb[2]));
}
