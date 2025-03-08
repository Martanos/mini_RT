/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:49:09 by malee             #+#    #+#             */
/*   Updated: 2025/03/08 10:02:13 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_add_cone(t_master **master, t_cone *cone)
{
	t_cone	*temp;

	temp = (*master)->cone_head;
	if (!(*master)->cone_head)
		(*master)->cone_head = cone;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = cone;
	}
}

static bool	ft_populate_cone(t_master **master, t_cone **cone, t_p_node **cur)
{
	(*cone)->cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*cone)->cord, -INFINITY, INFINITY,
			"Cone coordinates are not a valid vector") || !ft_next(cur,
			"Cone has no normal"))
		return (false);
	(*cone)->norm = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*cone)->norm, -1, 1,
			"Cone normal is not a valid vector") || !ft_next(cur,
			"Cone has no height"))
		return (false);
	(*cone)->height = ft_atod((*cur)->str);
	if ((*cone)->height <= 0)
		return (ft_error("Cone height is not a positive integer"));
	if (!ft_next(cur, "Cone has no diameter"))
		return (false);
	(*cone)->diameter = ft_atod((*cur)->str);
	if ((*cone)->diameter <= 0)
		return (ft_error("Cone diameter is not a positive integer"));
	if (!ft_next(cur, "Cone has no color"))
		return (false);
	if (!ft_get_rgb(&(*cone)->pro.txm.pri_color, (*cur)->str))
		return (false);
	return (ft_extra_data(master, &((*cone)->pro), cur));
}

// @brief Creates a plane object
// @param master pointer to the master structure
// @param cur pointer to the current node in the parser node list
// @return true if successful, false if error
bool	ft_create_cone(t_master **master, t_p_node **cur)
{
	t_cone	*cone;

	cone = (t_cone *)ft_calloc(1, sizeof(t_cone));
	if (!cone)
		return (false);
	if (!ft_next(cur, "Cone has no normal"))
		return (true);
	if (!ft_populate_cone(master, &cone, cur))
		return (free(cone), false);
	ft_add_cone(master, cone);
	return (true);
}
