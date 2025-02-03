/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:07:39 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/03 17:47:41 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

typedef struct s_intersection_info
{
	t_hit_record	hit;
	uint32_t		color;
}	t_intersection_info;

t_intersection_info find_closest_intersection(t_ray ray, t_data *mlx_data, t_master *master);
uint32_t	calculate_ambient_lighting(uint32_t obj_color, t_master *master)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	double	ambient;
	uint32_t	amb_color;
	uint8_t	amb_r;
	uint8_t	amb_g;
	uint8_t	amb_b;
	double	final_r;
	double	final_g;
	double	final_b;

	r = (uint8_t)((obj_color >> 16) & 0xFF);
	g = (uint8_t)((obj_color >> 8) & 0xFF);
	b = (uint8_t)(obj_color & 0xFF);
	ambient = master->amb_head->ratio;
	amb_color = master->amb_head->rgb;
	amb_r = (uint8_t)((amb_color >> 16) & 0xFF);
	amb_g = (uint8_t)((amb_color >> 8) & 0xFF);
	amb_b = (uint8_t)(amb_color & 0xFF);
	final_r = r * ambient * (amb_r / 255.0);
	final_g = g * ambient * (amb_g / 255.0);
	final_b = b * ambient * (amb_b / 255.0);
	r = (uint8_t)fmin(fmax(final_r, 0), 255);
	g = (uint8_t)fmin(fmax(final_g, 0), 255);
	b = (uint8_t)fmin(fmax(final_b, 0), 255);
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}

t_ray	calculate_shadow_ray(t_vect hit_point, t_vect light_pos, t_vect normal)
{
	t_ray	shadow_ray;
	t_vect	offset;

	offset = vect_multiply(normal, 0.001);
	shadow_ray.origin = vect_add(hit_point, offset);
	shadow_ray.direction = vect_normalize(vect_sub(light_pos, hit_point));
	return (shadow_ray);
}

bool	check_shadow_intersection(t_ray shadow_ray, double light_distance,
	t_data *mlx_data, t_master *master)
{
	t_sphere_collision	shadow_sphere;
	t_plane_collision	shadow_plane;
	t_cylinder_collision	shadow_cylinder;
	t_cone_collision	shadow_cone;

	shadow_sphere = find_closest_sphere(shadow_ray, mlx_data, master);
	shadow_plane = find_closest_plane(shadow_ray, mlx_data, master);
	shadow_cylinder = find_closest_cylinder(shadow_ray, mlx_data, master);
	shadow_cone = find_closest_cone(shadow_ray, mlx_data, master);
	return ((shadow_sphere.closest_sphere && shadow_sphere.closest_t < light_distance)
		|| (shadow_plane.closest_plane && shadow_plane.closest_t > 0.001
			&& shadow_plane.closest_t < light_distance)
		|| (shadow_cylinder.closest_cylinder && shadow_cylinder.closest_t < light_distance)
		|| (shadow_cone.closest_cone && shadow_cone.closest_t < light_distance));
}

uint32_t	calculate_light_contribution(t_hit_record hit, t_light *light,
	uint32_t obj_color)
{
	double	diff;
	double	intensity;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	light_r;
	uint8_t	light_g;
	uint8_t	light_b;
	double	final_r;
	double	final_g;
	double	final_b;
	t_vect	light_dir;

	r = (uint8_t)((obj_color >> 16) & 0xFF);
	g = (uint8_t)((obj_color >> 8) & 0xFF);
	b = (uint8_t)(obj_color & 0xFF);
	light_dir = vect_normalize(vect_sub(light->cord, hit.point));
	diff = fmax(vect_dot(hit.normal, light_dir), 0.0);
	intensity = light->intensity * diff;
	light_r = (uint8_t)((light->color >> 16) & 0xFF);
	light_g = (uint8_t)((light->color >> 8) & 0xFF);
	light_b = (uint8_t)(light->color & 0xFF);
	final_r = r * intensity * (light_r / 255.0);
	final_g = g * intensity * (light_g / 255.0);
	final_b = b * intensity * (light_b / 255.0);
	r = (uint8_t)fmin(fmax(final_r, 0), 255);
	g = (uint8_t)fmin(fmax(final_g, 0), 255);
	b = (uint8_t)fmin(fmax(final_b, 0), 255);
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}

t_intersection_info	find_closest_intersection(t_ray ray, t_data *mlx_data,
	t_master *master)
{
	t_intersection_info	info;
	t_sphere_collision	sphere_collision;
	t_plane_collision	plane_collision;
	t_cylinder_collision	cylinder_collision;
	t_cone_collision	cone_collision;

	sphere_collision = find_closest_sphere(ray, mlx_data, master);
	plane_collision = find_closest_plane(ray, mlx_data, master);
	cylinder_collision = find_closest_cylinder(ray, mlx_data, master);
	cone_collision = find_closest_cone(ray, mlx_data, master);
	if (sphere_collision.closest_sphere && (!plane_collision.closest_plane
			|| sphere_collision.closest_t < plane_collision.closest_t)
		&& (!cylinder_collision.closest_cylinder
			|| sphere_collision.closest_t < cylinder_collision.closest_t)
		&& (!cone_collision.closest_cone
			|| sphere_collision.closest_t < cone_collision.closest_t))
	{
		calculate_sphere_hit(ray, sphere_collision, &info.hit);
		info.color = sphere_collision.closest_sphere->rgb;
	}
	else if (plane_collision.closest_plane
		&& (!cylinder_collision.closest_cylinder
			|| plane_collision.closest_t < cylinder_collision.closest_t)
		&& (!cone_collision.closest_cone
			|| plane_collision.closest_t < cone_collision.closest_t))
	{
		calculate_plane_hit(ray, plane_collision, &info.hit);
		info.color = plane_collision.closest_plane->rgb;
	}
	else if (cylinder_collision.closest_cylinder
		&& (!cone_collision.closest_cone
			|| cylinder_collision.closest_t < cone_collision.closest_t))
	{
		calculate_cylinder_hit(ray, cylinder_collision, &info.hit);
		info.color = cylinder_collision.closest_cylinder->txm.pri_color;
	}
	else if (cone_collision.closest_cone)
	{
		calculate_cone_hit(ray, cone_collision, &info.hit);
		info.color = cone_collision.closest_cone->txm.pri_color;
	}
	else
		info.hit.t = 0;
	return (info);
}

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

	t = (unit_direction.y + 1.0) * 0.5;
	r = (uint8_t)((1.0 - t) * 0xFF + t * 0x00);
	g = (uint8_t)((1.0 - t) * 0xFF + t * 0x00);
	b = (uint8_t)((1.0 - t) * 0xFF + t * 0x00);
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}

uint32_t	ray_color(t_ray ray, t_data *mlx_data, t_master *master)
{
	t_intersection_info	info;
	t_vect				unit_direction;
	uint32_t			color;
	t_light				*light;
	t_ray				shadow_ray;
	double				light_distance;
	uint8_t				r;
	uint8_t				g;
	uint8_t				b;
	double				final_r;
	double				final_g;
	double				final_b;

	info = find_closest_intersection(ray, mlx_data, master);
	if (info.hit.t == 0)
	{
		unit_direction = vect_normalize(ray.direction);
		return (ft_background_color(unit_direction));
	}
	color = calculate_ambient_lighting(info.color, master);
	r = (uint8_t)((color >> 16) & 0xFF);
	g = (uint8_t)((color >> 8) & 0xFF);
	b = (uint8_t)(color & 0xFF);
	final_r = r;
	final_g = g;
	final_b = b;
	light = master->light_head;
	while (light)
	{
		light_distance = vect_magnitude(vect_sub(light->cord, info.hit.point));
		shadow_ray = calculate_shadow_ray(info.hit.point, light->cord, info.hit.normal);
		if (check_shadow_intersection(shadow_ray, light_distance, mlx_data, master))
		{
			light = light->next;
			continue ;
		}
		color = calculate_light_contribution(info.hit, light, info.color);
		final_r += (uint8_t)((color >> 16) & 0xFF);
		final_g += (uint8_t)((color >> 8) & 0xFF);
		final_b += (uint8_t)(color & 0xFF);
		light = light->next;
	}
	r = (uint8_t)fmin(fmax(final_r, 0), 255);
	g = (uint8_t)fmin(fmax(final_g, 0), 255);
	b = (uint8_t)fmin(fmax(final_b, 0), 255);
	return (0xFF000000 | (r << 16) | (g << 8) | b);
}
