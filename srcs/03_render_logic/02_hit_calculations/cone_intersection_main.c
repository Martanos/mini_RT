/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection_main.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:16:39 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 14:48:55 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * Main cone intersection function that checks all parts of the cone
 */
bool	ft_intersect_cone(t_scene **scene, t_obj_data *cone, t_hit **hit,
		t_ray **ray)
{
	t_quadratic	quad;
	bool		hit_anything;

	hit_anything = false;
	if (ft_intersect_cone_side(ray, cone, hit))
		hit_anything = true;
	if (ft_intersect_cone_base(ray, cone, hit))
		hit_anything = true;
	return (hit_anything);
}
