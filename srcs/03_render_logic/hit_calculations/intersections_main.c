/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:57:57 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 08:09:36 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * Dispatches to the appropriate intersection function based on object type
 * Updates hit only if this intersection is closer than the current hit
 */
static bool	ft_intersect_object(t_scene **scene, t_obj_data *obj)
{
	if (obj->type == SPHERE)
		return (ft_intersect_sphere(scene, obj));
	else if (obj->type == PLANE)
		return (ft_intersect_plane(scene, obj));
	else if (obj->type == CYLINDER)
		return (ft_intersect_cylinder(scene, obj));
	else if (obj->type == CONE)
		return (ft_intersect_cone(scene, obj));
	return (false);
}

bool	ft_intersect_main(t_scene **scene)
{
	bool hit;
	t_obj_data *current;

	current = (*scene)->obj_head;
	while (current)
	{
		if (ft_intersect_object(scene, current))
			hit = true;
		current = current->next;
	}
	return (hit);
}