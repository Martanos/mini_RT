/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:07:39 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/04 16:10:45 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

typedef struct s_intersection_info
{
	t_hit_record	hit;
	uint32_t		color;
}	t_intersection_info;

t_intersection_info find_closest_intersection(t_ray ray, t_master *master);

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

	offset = vect_multiply(normal, 0.001);
	shadow_ray.origin = vect_add(hit_point, offset);
	shadow_ray.direction = vect_normalize(vect_sub(light_pos, hit_point));
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
	return ((shadow_sphere.closest_sphere && shadow_sphere.closest_t < light_distance)
		|| (shadow_plane.closest_plane && shadow_plane.closest_t > 0.001
			&& shadow_plane.closest_t < light_distance)
		|| (shadow_cylinder.closest_cylinder && shadow_cylinder.closest_t < light_distance)
		|| (shadow_cone.closest_cone && shadow_cone.closest_t < light_distance));
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

	light_dir = vect_normalize(vect_sub(light->cord, hit.point));
	diff = fmax(vect_dot(hit.normal, light_dir), 0.0);
	intensity = light->ratio * diff;
	ft_convert_rgb_arr(obj_color, rgb);
	ft_convert_rgb_arr(light->color, light_rgb);
	final[0] = rgb[0] * intensity * (light_rgb[0] / 255.0);
	final[1] = rgb[1] * intensity * (light_rgb[1] / 255.0);
	final[2] = rgb[2] * intensity * (light_rgb[2] / 255.0);
	ft_clamp_rgb_values(final, rgb);
	return (ft_create_rgb(rgb[0], rgb[1], rgb[2]));
}

static void update_closest_intersection(t_intersection_info *closest, 
    t_intersection_info current)
{
    if (current.hit.t > 0 && (!closest->hit.t || current.hit.t < closest->hit.t))
    {
        *closest = current;
    }
}

t_intersection_info find_closest_intersection(t_ray ray, t_master *master)
{
    t_intersection_info closest = {0};
    t_intersection_info current;

    // Test sphere intersection
    t_sphere_collision sphere = find_closest_sphere(ray, master);
    if (sphere.closest_sphere)
    {
        calculate_sphere_hit(ray, sphere, &current.hit);
        current.color = sphere.closest_sphere->pro.txm.pri_color;
        update_closest_intersection(&closest, current);
    }

    // Test plane intersection
    t_plane_collision plane = find_closest_plane(ray, master);
    if (plane.closest_plane)
    {
        calculate_plane_hit(ray, plane, &current.hit);
        current.color = plane.closest_plane->pro.txm.pri_color;
        update_closest_intersection(&closest, current);
    }

    // Test cylinder intersection
    t_cylinder_collision cylinder = find_closest_cylinder(ray, master);
    if (cylinder.closest_cylinder)
    {
        calculate_cylinder_hit(ray, cylinder, &current.hit);
        current.color = cylinder.closest_cylinder->pro.txm.pri_color;
        update_closest_intersection(&closest, current);
    }

    // Test cone intersection
    t_cone_collision cone = find_closest_cone(ray, master);
    if (cone.closest_cone)
    {
        calculate_cone_hit(ray, cone, &current.hit);
        current.color = cone.closest_cone->pro.txm.pri_color;
        update_closest_intersection(&closest, current);
    }

    return closest;
}

/**
 * @brief Calculates the background color based on the unit direction vector
 * @param unit_direction The unit direction vector
 * @return uint32_t The background color
 */
uint32_t	ft_background_color(t_vect unit_direction)
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
		return (ft_background_color(vect_normalize(ray.direction)));
	color = calculate_ambient_lighting(info.color, master);
	ft_convert_rgb_arr(color, rgb);
	final[0] = rgb[0];
	final[1] = rgb[1];
	final[2] = rgb[2];
	light = master->light_head;
	while (light)
	{
		light_distance = vect_magnitude(vect_sub(light->cord, info.hit.point));
		shadow_ray = calculate_shadow_ray(info.hit.point, light->cord, info.hit.normal);
		if (check_shadow_intersection(shadow_ray, light_distance, master))
		{
			light = light->next;
			continue ;
		}
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
