/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection_main.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:16:39 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 08:01:36 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * Main cone intersection function that checks all parts of the cone
 */
bool	ft_intersect_cone(t_scene **scene, t_obj_data *cone)
{
	t_quadratic	quad;
	bool		hit_anything;
	t_hit		temp_hit;

	hit_anything = false;
	temp_hit = (*scene)->z_buffer[0];
	if (ft_intersect_cone_side((*scene)->ray_buffer, cone, &quad, &temp_hit))
	{
		(*scene)->z_buffer[0] = temp_hit;
		hit_anything = true;
	}
	if (ft_intersect_cone_base((*scene)->ray_buffer, cone, &temp_hit))
	{
		(*scene)->z_buffer[0] = temp_hit;
		hit_anything = true;
	}
	return (hit_anything);
}
