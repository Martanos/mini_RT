/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:07:50 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/07 16:51:01 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "plane.h"

double	check_plane_collision(t_ray ray, t_plane_obj *plane)
{
	double	denom;
	t_vect	p0l0;
	double	t;

	denom = vect_dot(plane->plane_normal, ray.direction);
	if (fabs(denom) < 1e-6)  // Ray is parallel to plane
		return (-1.0);

	p0l0 = vect_sub(plane->plane_pos, ray.origin);
	t = vect_dot(p0l0, plane->plane_normal) / denom;

	if (t < 0.0)  // Plane is behind ray
		return (-1.0);
	return (t);
}

t_plane_collision	find_closest_plane(t_ray ray, t_data *mlx_data)
{
	double			t;
	t_plane_collision result;
	t_plane_obj		*plane;
	int				i;

	i = 0;
	result.closest_t = INFINITY;
	result.closest_plane = NULL;
	while (mlx_data->instruction_set->plane_obj_list[i])
	{
		plane = mlx_data->instruction_set->plane_obj_list[i];
		t = check_plane_collision(ray, plane);
		if (t > 0.0 && t < result.closest_t)
		{
			result.closest_t = t;
			result.closest_plane = plane;
		}
		i++;
	}
	return (result);
}