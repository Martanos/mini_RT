/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:45:00 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/08 16:04:39 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "plane.h"

static double	check_height(t_ray ray, double t, t_cylinder_obj *cylinder)
{
	t_vect	intersection;
	t_vect	v;
	double	height;

	intersection = vect_add(ray.origin, vect_multiply(ray.direction, t));
	v = vect_sub(intersection, cylinder->cylinder_pos);
	height = vect_dot(v, cylinder->cylinder_normal);
	if (height >= 0 && height <= cylinder->cylinder_height)
		return (t);
	return (-1.0);
}

double	check_cylinder_collision(t_ray ray, t_cylinder_obj *cylinder)
{
	t_vect	oc;
	t_vect	cross_dir_normal;
	double	radius;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;

	oc = vect_sub(ray.origin, cylinder->cylinder_pos);
	cross_dir_normal = vect_cross(ray.direction, cylinder->cylinder_normal);
	radius = cylinder->cylinder_diameter / 2.0;

	a = vect_dot(cross_dir_normal, cross_dir_normal);
	b = 2.0 * vect_dot(cross_dir_normal, vect_cross(oc, cylinder->cylinder_normal));
	c = vect_dot(vect_cross(oc, cylinder->cylinder_normal), 
		vect_cross(oc, cylinder->cylinder_normal)) - (radius * radius);

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);

	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);

	// Check if intersection points are within cylinder height
	if (t1 > 0.0)
	{
		t1 = check_height(ray, t1, cylinder);
		if (t1 > 0.0)
			return (t1);
	}
	if (t2 > 0.0)
	{
		t2 = check_height(ray, t2, cylinder);
		if (t2 > 0.0)
			return (t2);
	}
	return (-1.0);
}

t_cylinder_collision	find_closest_cylinder(t_ray ray, t_data *mlx_data)
{
	double				t;
	t_cylinder_collision	result;
	t_cylinder_obj		*cylinder;
	int					i;

	i = 0;
	result.closest_t = INFINITY;
	result.closest_cylinder = NULL;
	while (mlx_data->instruction_set->cylinder_obj_list[i])
	{
		cylinder = mlx_data->instruction_set->cylinder_obj_list[i];
		t = check_cylinder_collision(ray, cylinder);
		if (t > 0.0 && t < result.closest_t)
		{
			result.closest_t = t;
			result.closest_cylinder = cylinder;
		}
		i++;
	}
	return (result);
}

void	calculate_cylinder_hit(t_ray ray, t_cylinder_collision collision, t_hit_record *rec)
{
	rec->t = collision.closest_t;
	rec->point = vect_add(ray.origin, vect_multiply(ray.direction, collision.closest_t));
	
	// Calculate normal at hit point on cylinder surface
	t_vect cp = vect_sub(rec->point, collision.closest_cylinder->cylinder_pos);
	double proj = vect_dot(cp, collision.closest_cylinder->cylinder_normal);
	t_vect axis_point = vect_add(collision.closest_cylinder->cylinder_pos,
		vect_multiply(collision.closest_cylinder->cylinder_normal, proj));
	rec->normal = vect_normalize(vect_sub(rec->point, axis_point));
}
