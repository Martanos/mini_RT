/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection_main.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:16:39 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 10:43:35 by malee            ###   ########.fr       */
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
	temp_hit = (*scene)->hit;
	if (ft_intersect_cone_side(&(*scene)->ray, cone, &quad, &temp_hit))
	{
		(*scene)->hit = temp_hit;
		hit_anything = true;
	}
	if (ft_intersect_cone_base(&(*scene)->ray, cone, &temp_hit))
	{
		(*scene)->hit = temp_hit;
		hit_anything = true;
	}
	return (hit_anything);
}
