/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:57:57 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 12:05:42 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * Dispatches to the appropriate intersection function based on object type
 * Updates hit only if this intersection is closer than the current hit
 */
static bool	ft_intersect_object(t_scene **scene, t_obj_data *obj, t_hit **hit,
		t_ray **ray)
{
	if (obj->type == PLANE)
		return (ft_intersect_plane(scene, obj, hit, ray));
	else if (obj->type == SPHERE)
		return (ft_intersect_sphere(scene, obj, hit, ray));
	else if (obj->type == CYLINDER)
		return (ft_intersect_cylinder(scene, obj, hit, ray));
	else if (obj->type == CONE)
		return (ft_intersect_cone(scene, obj, hit, ray));
	return (false);
}

bool	ft_closest_hit(t_scene **scene, t_hit **hit, t_ray **ray)
{
	bool		hit;
	t_obj_data	*current;

	current = (*scene)->obj_head;
	while (current)
	{
		if (ft_intersect_object(scene, current, hit, ray))
			hit = true;
		current = current->next;
	}
	return (hit);
}
