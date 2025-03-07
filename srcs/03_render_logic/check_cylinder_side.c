/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder_side.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sean <sean@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:35:48 by sean              #+#    #+#             */
/*   Updated: 2025/03/04 14:38:45 by sean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

static t_vect	get_cylinder_cross_products(t_ray ray, t_cylinder *cylinder,
	t_vect *cross_oc_normal)
{
	t_vect	oc;
	t_vect	normalized_normal;
	t_vect	cross_dir_normal;

	oc = ft_vect_sub(ray.origin, cylinder->cord);
	normalized_normal = ft_vect_norm(cylinder->norm);
	cross_dir_normal = ft_vect_cross(ray.direction, normalized_normal);
	*cross_oc_normal = ft_vect_cross(oc, normalized_normal);
	return (cross_dir_normal);
}

static void	get_cylinder_quadratic(t_ray ray, t_cylinder *cylinder,
	double *coef)
{
	t_vect	cross_dir_normal;
	t_vect	cross_oc_normal;
	double	radius;

	cross_dir_normal = get_cylinder_cross_products(ray, cylinder,
			&cross_oc_normal);
	radius = cylinder->diameter / 2.0;
	coef[0] = ft_vect_dot(cross_dir_normal, cross_dir_normal);
	coef[1] = 2.0 * ft_vect_dot(cross_dir_normal, cross_oc_normal);
	coef[2] = ft_vect_dot(cross_oc_normal, cross_oc_normal)
		- (radius * radius);
}

static double	solve_cylinder_quadratic(double *coef, t_ray ray,
	t_cylinder *cylinder)
{
	double	discriminant;
	double	t;

	discriminant = coef[1] * coef[1] - 4 * coef[0] * coef[2];
	if (discriminant < 0)
		return (-1.0);
	t = (-coef[1] - sqrt(discriminant)) / (2.0 * coef[0]);
	if (t > 0.0)
	{
		t = check_cylinder_height(ray, t, cylinder);
		if (t > 0.0)
			return (t);
	}
	t = (-coef[1] + sqrt(discriminant)) / (2.0 * coef[0]);
	if (t > 0.0)
	{
		t = check_cylinder_height(ray, t, cylinder);
		if (t > 0.0)
			return (t);
	}
	return (-1.0);
}

double	check_cylinder_side(t_ray ray, t_cylinder *cylinder)
{
	double	coef[3];

	get_cylinder_quadratic(ray, cylinder, coef);
	return (solve_cylinder_quadratic(coef, ray, cylinder));
}
