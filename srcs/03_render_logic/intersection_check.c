/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:37:45 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/08 09:59:43 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

bool	check_shadow_intersection(t_ray shadow_ray, double light_distance,
		t_master *master)
{
	t_sphere_collision		shadow_sphere;
	t_plane_collision		shadow_plane;
	t_cylinder_collision	shadow_cylinder;
	t_cone_collision		shadow_cone;

	shadow_sphere = find_closest_sphere(shadow_ray, master);
	shadow_plane = find_closest_plane(shadow_ray, master);
	shadow_cylinder = find_closest_cylinder(shadow_ray, master);
	shadow_cone = find_closest_cone(shadow_ray, master);
	if (shadow_sphere.closest_sphere
		&& shadow_sphere.closest_t < light_distance)
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

t_intersect_info	find_closest_intersection(t_ray ray, t_master *master)
{
	t_intersect_info	closest;

	closest = (t_intersect_info){0};
	check_sphere_intersection(ray, master, &closest);
	check_plane_intersection(ray, master, &closest);
	check_cylinder_intersection(ray, master, &closest);
	check_cone_intersection(ray, master, &closest);
	return (closest);
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
