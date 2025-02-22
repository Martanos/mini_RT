/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:32:13 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 22:41:46 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// @brief Creates a sphere object
// @param master pointer to the master structure
// @param cur pointer to the current node in the parser node list
// @return true if successful, false if error
static bool	ft_populate_sphere(t_scene **scene, t_obj_data **obj,
		t_p_node **cur)
{
	if (!ft_next(cur, "Sphere has no coordinates"))
		return (false);
	(*obj)->cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*obj)->cord, -INFINITY, INFINITY,
			"Sphere coordinates are not a valid vector") || !ft_next(cur,
			"Sphere has no diameter"))
		return (false);
	(*obj)->props.sphere.diameter = ft_atod((*cur)->str);
	if (!ft_inrange((*obj)->props.sphere.diameter, 0, INFINITY))
		return (ft_error("Sphere diameter is not a positive number"));
	if (!ft_next(cur, "Sphere has no color"))
		return (false);
	if (!ft_get_rgb(&(*obj)->txm.pri_color, (*cur)->str))
		return (false);
	return (ft_extra_data(scene, &((*obj)->props), cur));
}

bool	ft_create_sphere(t_scene **scene, t_p_node **cur, t_obj_type type)
{
	t_obj_data	*obj;

	obj = (t_obj_data *)ft_calloc(1, sizeof(t_obj_data));
	if (!obj)
		return (false);
	obj->type = type;
	if (!ft_populate_sphere(scene, &obj, cur))
		return (free(obj), false);
	ft_add_obj(scene, obj);
	printf(GREEN "Sphere created successfully\n" RESET);
	return (true);
}
