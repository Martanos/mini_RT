/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection_main.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:17:30 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 12:37:01 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * Main cylinder intersection function that checks all parts of the cylinder
 */
bool	ft_intersect_cylinder(t_scene **scene, t_obj_data *cylinder,
		t_hit **hit, t_ray **ray)
{
	t_quadratic	quad;
	bool		hit_anything;

	hit_anything = false;
	quad = (t_quadratic){0};
	if (ft_intersect_cylinder_side(ray, cylinder, &quad, hit))
		hit_anything = true;
	if (ft_intersect_cylinder_cap(ray, cylinder, hit, true))
		hit_anything = true;
	if (ft_intersect_cylinder_cap(ray, cylinder, hit, false))
		hit_anything = true;
	return (hit_anything);
}
