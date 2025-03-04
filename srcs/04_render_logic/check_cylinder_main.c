/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sean <sean@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:35:48 by sean              #+#    #+#             */
/*   Updated: 2025/03/04 14:45:14 by sean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

double	check_cylinder_collision(t_ray ray, t_cylinder *cylinder)
{
	double	t_side;
	double	t_caps;
	double	closest_t;

	closest_t = INFINITY;
	t_side = check_cylinder_side(ray, cylinder);
	t_caps = check_cylinder_caps(ray, cylinder);
	if (t_side > 0.0 && t_side < closest_t)
		closest_t = t_side;
	if (t_caps > 0.0 && t_caps < closest_t)
		closest_t = t_caps;
	if (closest_t == INFINITY)
		return (-1.0);
	return (closest_t);
}

t_cylinder_collision	find_closest_cylinder(t_ray ray, t_master *master)
{
	double					t;
	t_cylinder_collision	result;
	t_cylinder				*cylinder;

	result.closest_t = INFINITY;
	result.closest_cylinder = NULL;
	cylinder = master->cylinder_head;
	while (cylinder)
	{
		t = check_cylinder_collision(ray, cylinder);
		if (t > 0.0 && t < result.closest_t)
		{
			result.closest_t = t;
			result.closest_cylinder = cylinder;
			if (t < EPSILON)
				break ;
		}
		cylinder = cylinder->next;
	}
	return (result);
}

void	calculate_cylinder_hit(t_ray ray, t_cylinder_collision collision,
		t_hit_record *rec)
{
	t_vect	cp;
	t_vect	normalized_normal;
	double	proj;

	rec->t = collision.closest_t;
	rec->point = ft_vect_add(ray.origin, ft_vect_mul_all(ray.direction,
				collision.closest_t));
	cp = ft_vect_sub(rec->point, collision.closest_cylinder->cord);
	normalized_normal = ft_vect_norm(collision.closest_cylinder->norm);
	proj = ft_vect_dot(cp, normalized_normal);
	rec->normal = get_cylinder_normal(rec->point, collision.closest_cylinder,
			proj);
}
