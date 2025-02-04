/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:40:56 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/04 16:23:29 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "libvect.h"

double	check_sphere_collision(t_ray ray, t_sphere *sphere)
{
	t_vect	oc = ft_vect_sub(ray.origin, sphere->cord);
	double	a = ft_vect_dot(ray.direction, ray.direction);
	double	b = 2.0 * ft_vect_dot(ray.direction, oc);
	double	c;
	double	discriminant;
	double	radius;
	double	t;

	radius = sphere->diameter / 2.0;
	c = ft_vect_dot(oc, oc) - (radius * radius);
	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (-1.0);
	
	// Try smaller t first (closer intersection)
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t > 0.0)  // Hit is in front of camera
		return (t);
	
	// Try larger t if smaller t is behind camera
	// t = (-b + sqrt(discriminant)) / (2.0 * a);
	// if (t > 0.0)
	// 	return (t);
	
	return (-1.0);  // Both hits are behind camera
}

t_sphere_collision	find_closest_sphere(t_ray ray, t_master *master)
{
	double			t;
	t_sphere_collision result;
	t_sphere	*sphere;

	result.closest_t = INFINITY;
	result.closest_sphere = NULL;
	sphere = master->sphere_head;
	while (sphere)
	{
		t = check_sphere_collision(ray, sphere);
		if (t > 0.0 && t < result.closest_t)
		{
			result.closest_t = t;
			result.closest_sphere = sphere;
		}
		sphere = sphere->next;
	}
	return (result);
}

void	calculate_sphere_hit(t_ray ray, t_sphere_collision collision, t_hit_record *rec)
{
	rec->t = collision.closest_t;
	rec->point = ft_vect_add(ray.origin, ft_vect_mul_all(ray.direction, collision.closest_t));
	rec->normal = ft_vect_norm(ft_vect_sub(rec->point, collision.closest_sphere->cord));
}
