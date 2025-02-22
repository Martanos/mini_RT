/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:28:42 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 22:44:24 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_populate_cylinder(t_scene **scene, t_obj_data **obj,
		t_p_node **cur)
{
	(*obj)->cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*obj)->cord, -INFINITY, INFINITY,
			"Cylinder coordinates are not a valid vector") || !ft_next(cur,
			"Cylinder has no normal"))
		return (false);
	(*obj)->dir = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*obj)->dir, -1, 1,
			"Cylinder coordinates are not a valid vector") || !ft_next(cur,
			"Cylinder has no diameter"))
		return (false);
	(*obj)->props.cylinder.diameter = ft_atod((*cur)->str);
	if (!ft_inrange((*obj)->props.cylinder.diameter, 0, INFINITY))
		return (ft_error("Cylinder diameter is not a valid double"));
	if (!ft_next(cur, "Cylinder has no height"))
		return (false);
	(*obj)->props.cylinder.height = ft_atod((*cur)->str);
	if (!ft_inrange((*obj)->props.cylinder.height, 0, INFINITY))
		return (ft_error("Cylinder height is not a valid double"));
	if (!ft_next(cur, "Cylinder has no color"))
		return (false);
	if (!ft_get_rgb(&(*obj)->txm.pri_color, (*cur)->str))
		return (false);
	return (ft_extra_data(scene, &((*obj)->props), cur));
}

bool	ft_create_cylinder(t_scene **scene, t_p_node **cur, t_obj_type type)
{
	t_obj_data	*obj;

	obj = (t_obj_data *)ft_calloc(1, sizeof(t_obj_data));
	if (!obj)
		return (false);
	obj->type = type;
	(*cur) = (*cur)->next;
	if (!ft_populate_cylinder(scene, &obj, cur))
		return (free(obj), false);
	ft_add_obj(scene, obj);
	printf(GREEN "Cylinder created successfully\n" RESET);
	return (true);
}
