/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:40:56 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/07 13:41:31 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "plane.h"

double	check_sphere_collision(t_ray ray, t_sphere_obj *sphere)
{
	t_vect	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	radius;
	double	t;

	oc = vect_sub(ray.origin, sphere->sphere_pos);
	a = vect_dot(ray.direction, ray.direction);
	b = 2.0 * vect_dot(ray.direction, oc);
	radius = sphere->sphere_diameter / 2.0;
	c = vect_dot(oc, oc) - (radius * radius);
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

t_sphere_collision	find_closest_sphere(t_ray ray, t_data *mlx_data)
{
	double			t;
	t_sphere_collision result;
	t_sphere_obj	*sphere;
	int				i;

	i = 0;
	result.closest_t = INFINITY;
	result.closest_sphere = NULL;
	while (mlx_data->instruction_set->sphere_obj_list[i])
	{
		sphere = mlx_data->instruction_set->sphere_obj_list[i];
		t = check_sphere_collision(ray, sphere);
		if (t > 0.0 && t < result.closest_t)
		{
			result.closest_t = t;
			result.closest_sphere = sphere;
		}
		i++;
	}
	return (result);
}