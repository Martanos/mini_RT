/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sean <sean@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:34:48 by sean              #+#    #+#             */
/*   Updated: 2025/03/04 14:38:23 by sean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_vect	get_intersection_point(t_ray ray, double t)
{
	return (ft_vect_add(ray.origin, ft_vect_mul_all(ray.direction, t)));
}

double	check_cylinder_height(t_ray ray, double t, t_cylinder *cylinder)
{
	t_vect	v;
	double	height;
	t_vect	normalized_normal;

	v = ft_vect_sub(get_intersection_point(ray, t), cylinder->cord);
	normalized_normal = ft_vect_norm(cylinder->norm);
	height = ft_vect_dot(v, normalized_normal);
	if (height >= -cylinder->height / 2 && height <= cylinder->height / 2)
		return (t);
	return (-1.0);
}

t_vect	get_cylinder_normal(t_vect point, t_cylinder *cylinder, double proj)
{
	t_vect	normalized_normal;
	t_vect	axis_point;
	double	half_height;

	normalized_normal = ft_vect_norm(cylinder->norm);
	half_height = cylinder->height / 2.0;
	if (fabs(proj + half_height) < 1e-6)
		return (ft_vect_mul_all(normalized_normal, -1));
	if (fabs(proj - half_height) < 1e-6)
		return (normalized_normal);
	axis_point = ft_vect_add(cylinder->cord,
			ft_vect_mul_all(normalized_normal, proj));
	return (ft_vect_norm(ft_vect_sub(point, axis_point)));
}
