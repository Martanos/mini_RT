/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection_main.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:17:30 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 07:42:30 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * Main cylinder intersection function that checks all parts of the cylinder
 */
bool	ft_intersect_cylinder(t_scene **scene, t_obj_data *cylinder)
{
	t_quadratic	quad;
	bool		hit_anything;
	t_hit		temp_hit;

	hit_anything = false;
	temp_hit = (*scene)->z_buffer[0];
	if (ft_intersect_cylinder_side((*scene)->ray_buffer, cylinder, &quad,
			&temp_hit))
	{
		(*scene)->z_buffer[0] = temp_hit;
		hit_anything = true;
	}
	if (ft_intersect_cylinder_cap((*scene)->ray_buffer, cylinder, &temp_hit,
			true))
	{
		(*scene)->z_buffer[0] = temp_hit;
		hit_anything = true;
	}
	if (ft_intersect_cylinder_cap((*scene)->ray_buffer, cylinder, &temp_hit,
			false))
	{
		(*scene)->z_buffer[0] = temp_hit;
		hit_anything = true;
	}
	return (hit_anything);
}
