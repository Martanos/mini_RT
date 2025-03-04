/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder_caps.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sean <sean@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:35:48 by sean              #+#    #+#             */
/*   Updated: 2025/03/04 14:35:31 by sean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

static void	setup_cap_plane(t_plane *cap, t_cylinder *cylinder,
	t_vect normal, double height_offset)
{
	cap->cord = ft_vect_add(cylinder->cord,
			ft_vect_mul_all(normal, height_offset));
	cap->norm = normal;
	cap->radius = cylinder->diameter / 2.0;
}

static double	check_cap_collision(t_ray ray, t_plane *cap)
{
	double	t;

	t = check_plane_collision(ray, cap);
	if (t > 0.0)
		return (t);
	return (INFINITY);
}

double	check_cylinder_caps(t_ray ray, t_cylinder *cylinder)
{
	t_vect	normalized_normal;
	t_plane	bottom_cap;
	t_plane	top_cap;
	double	t1;
	double	t2;

	normalized_normal = ft_vect_norm(cylinder->norm);
	setup_cap_plane(&bottom_cap, cylinder,
		ft_vect_mul_all(normalized_normal, -1), -cylinder->height / 2);
	setup_cap_plane(&top_cap, cylinder,
		normalized_normal, cylinder->height / 2);
	t1 = check_cap_collision(ray, &bottom_cap);
	t2 = check_cap_collision(ray, &top_cap);
	if (t1 == INFINITY && t2 == INFINITY)
		return (-1.0);
	if (t1 == INFINITY)
		return (t2);
	if (t2 == INFINITY)
		return (t1);
	return (fmin(t1, t2));
}
