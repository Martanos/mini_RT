/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:49:09 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 22:44:03 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_populate_cone(t_scene **scene, t_obj_data **obj, t_p_node **cur)
{
	(*obj)->cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*obj)->cord, -INFINITY, INFINITY,
			"Cone coordinates are not a valid vector") || !ft_next(cur,
			"Cone has no normal"))
		return (false);
	(*obj)->dir = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*obj)->dir, -1, 1,
			"Cone normal is not a valid vector") || !ft_next(cur,
			"Cone has no height"))
		return (false);
	(*obj)->props.cone.height = ft_atod((*cur)->str);
	if ((*obj)->props.cone.height <= 0)
		return (ft_error("Cone height is not a positive integer"));
	if (!ft_next(cur, "Cone has no diameter"))
		return (false);
	(*obj)->props.cone.diameter = ft_atod((*cur)->str);
	if ((*obj)->props.cone.diameter <= 0)
		return (ft_error("Cone diameter is not a positive integer"));
	if (!ft_next(cur, "Cone has no color"))
		return (false);
	if (!ft_get_rgb(&(*obj)->txm.pri_color, (*cur)->str))
		return (false);
	return (ft_extra_data(scene, &((*obj)->props), cur));
}

// @brief Creates a plane object
// @param master pointer to the master structure
// @param cur pointer to the current node in the parser node list
// @return true if successful, false if error
bool	ft_create_cone(t_scene **scene, t_p_node **cur, t_obj_type type)
{
	t_obj_data	*obj;

	obj = (t_obj_data *)ft_calloc(1, sizeof(t_obj_data));
	if (!obj)
		return (false);
	obj->type = type;
	if (!ft_next(cur, "Cone has no normal"))
		return (true);
	if (!ft_populate_cone(scene, &obj, cur))
		return (free(obj), false);
	ft_add_obj(scene, &obj);
	printf(GREEN "Cone created successfully\n" RESET);
	return (true);
}
