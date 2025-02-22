/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:10:18 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 22:42:08 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_populate_plane(t_scene **scene, t_obj_data **obj, t_p_node **cur)
{
	if (!ft_next(cur, "Plane has no coordinates"))
		return (false);
	(*obj)->cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*obj)->cord, -INFINITY, INFINITY,
			"Plane coordinates are not a valid vector") || !ft_next(cur,
			"Plane has no normal"))
		return (false);
	(*obj)->dir = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*obj)->dir, -1, 1,
			"Plane coordinates are not a valid vector") || !ft_next(cur,
			"Plane has no color"))
		return (false);
	if (!ft_get_rgb(&(*obj)->txm.pri_color, (*cur)->str))
		return (false);
	return (ft_extra_data(scene, &((*obj)->mat), cur));
}

// @brief Creates a plane object
// @param master pointer to the master structure
// @param cur pointer to the current node in the parser node list
// @return true if successful, false if error
bool	ft_create_plane(t_scene **scene, t_p_node **cur, t_obj_type type)
{
	t_obj_data	*obj;

	obj = (t_obj_data *)ft_calloc(1, sizeof(t_obj_data));
	if (!obj)
		return (false);
	obj->type = type;
	if (!ft_populate_plane(scene, &obj, cur))
		return (free(obj), false);
	ft_add_obj(scene, &obj);
	printf(GREEN "Plane created successfully\n" RESET);
	return (true);
}
