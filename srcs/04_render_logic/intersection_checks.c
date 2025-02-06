/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_checks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:25:00 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/06 17:06:37 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void	update_closest_intersection(t_intersection_info *closest,
		t_intersection_info current)
{
	if (current.hit.t > 0 && (!closest->hit.t
			|| current.hit.t < closest->hit.t))
		*closest = current;
}

void	check_sphere_intersection(t_ray ray, t_master *master,
		t_intersection_info *closest)
{
	t_intersection_info	current;
	t_sphere_collision	sphere;

	sphere = find_closest_sphere(ray, master);
	if (sphere.closest_sphere)
	{
		calculate_sphere_hit(ray, sphere, &current.hit);
		current.color = sphere.closest_sphere->pro.txm.pri_color;
		update_closest_intersection(closest, current);
	}
}

void	check_plane_intersection(t_ray ray, t_master *master,
		t_intersection_info *closest)
{
	t_intersection_info	current;
	t_plane_collision	plane;

	plane = find_closest_plane(ray, master);
	if (plane.closest_plane)
	{
		calculate_plane_hit(ray, plane, &current.hit);
		current.color = plane.closest_plane->pro.txm.pri_color;
		update_closest_intersection(closest, current);
	}
}

void	check_cylinder_intersection(t_ray ray, t_master *master,
		t_intersection_info *closest)
{
	t_intersection_info		current;
	t_cylinder_collision	cylinder;

	cylinder = find_closest_cylinder(ray, master);
	if (cylinder.closest_cylinder)
	{
		calculate_cylinder_hit(ray, cylinder, &current.hit);
		current.color = cylinder.closest_cylinder->pro.txm.pri_color;
		update_closest_intersection(closest, current);
	}
}

void	check_cone_intersection(t_ray ray, t_master *master,
		t_intersection_info *closest)
{
	t_intersection_info	current;
	t_cone_collision	cone;

	cone = find_closest_cone(ray, master);
	if (cone.closest_cone)
	{
		calculate_cone_hit(ray, cone, &current.hit);
		current.color = cone.closest_cone->pro.txm.pri_color;
		update_closest_intersection(closest, current);
	}
}
