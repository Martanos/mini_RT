/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:49:09 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 20:54:44 by malee            ###   ########.fr       */
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

static bool	ft_check_extra_data(t_master **master, t_cone **cone,
		t_p_node **cur)
{
	while (*cur)
	{
		if (ft_strcmp((*cur)->str, "txm:") == 0)
		{
			if (!ft_add_cone_texture(master, cone, (*cur)->str + 4))
				return (false);
		}
		else if (ft_strcmp((*cur)->str, "bpm:") == 0)
		{
			if (!ft_add_cone_bump_map(master, cone, (*cur)->str + 4))
				return (false);
		}
		else if (ft_strcmp((*cur)->str, "mat:"))
		{
			if (!ft_add_cone_material(cone, (*cur)->str + 4))
				return (false);
		}
		else
			return (ft_format_error("Unknown cone data"));
		(*cur) = (*cur)->next;
	}
	return (true);
}

static bool	ft_populate_cone(t_master **master, t_cone **cone, t_p_node **cur)
{
	(*cone)->cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*cone)->cord, -INFINITY, INFINITY))
		return (ft_format_error("Cone coordinates are not a valid vector"));
	(*cur) = (*cur)->next;
	(*cone)->norm = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*cone)->norm, -1, 1))
		return (ft_format_error("Cone coordinates are not a valid vector"));
	(*cur) = (*cur)->next;
	(*cone)->height = ft_atod((*cur)->str);
	if ((*cone)->height <= 0)
		return (ft_format_error("Cone height is not a positive number"));
	(*cur) = (*cur)->next;
	(*cone)->diameter = ft_atod((*cur)->str);
	if ((*cone)->diameter <= 0)
		return (ft_format_error("Cone diameter is not a positive number"));
	(*cur) = (*cur)->next;
	(*cone)->txm.pri_color = ft_get_rgb((*cur)->str);
	if ((*cone)->txm.pri_color < 0 || (*cone)->txm.pri_color > 0xFFFFFF)
		return (ft_format_error("Cone color is out of range [0,255]"));
	(*cur) = (*cur)->next;
	if (*cur && !ft_check_extra_data(master, cone, cur))
		return (false);
	return (true);
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
	(*cur) = (*cur)->next;
	if (!ft_populate_cone(master, &cone, cur))
		return (free(cone), false);
	ft_add_cone(master, cone);
	return (true);
}
