/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:28:42 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 20:41:12 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_add_cylinder(t_master **master, t_cylinder *cylinder)
{
	t_cylinder	*temp;

	temp = (*master)->plane_head;
	if (!(*master)->cylinder_head)
		(*master)->cylinder_head = cylinder;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = cylinder;
	}
}

static bool	ft_check_extra_data(t_master **master, t_cylinder **cylinder,
		t_p_node **cur)
{
	while (*cur)
	{
		if (ft_strcmp((*cur)->str, "txm:") == 0)
		{
			if (!ft_add_cylinder_texture(master, cylinder, (*cur)->str + 4))
				return (false);
		}
		else if (ft_strcmp((*cur)->str, "bpm:") == 0)
		{
			if (!ft_add_cylinder_bump_map(master, cylinder, (*cur)->str + 4))
				return (false);
		}
		else if (ft_strcmp((*cur)->str, "mat:"))
		{
			if (!ft_add_cylinder_material(cylinder, (*cur)->str + 4))
				return (false);
		}
		else
			return (ft_format_error("Unknown cylinder data"));
		(*cur) = (*cur)->next;
	}
	return (true);
}

static bool	ft_populate_cylinder(t_master **master, t_cylinder **cylinder,
		t_p_node **cur)
{
	(*cylinder)->cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*cylinder)->cord, -INFINITY, INFINITY))
		return (ft_format_error("Cylinder coordinates are not a valid vector"));
	(*cur) = (*cur)->next;
	(*cylinder)->norm = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*cylinder)->norm, -1, 1))
		return (ft_format_error("Cylinder coordinates are not a valid vector"));
	(*cur) = (*cur)->next;
	(*cylinder)->diameter = ft_atod((*cur)->str);
	if (!ft_inrange((*cylinder)->diameter, 0, INFINITY))
		return (ft_format_error("Cylinder diameter is not a valid double"));
	(*cur) = (*cur)->next;
	(*cylinder)->height = ft_get_double(cur);
	if (!ft_inrange((*cylinder)->height, 0, INFINITY))
		return (ft_format_error("Cylinder height is not a valid double"));
	(*cylinder)->txm.pri_color = ft_get_rgb((*cur)->str);
	if ((*cylinder)->txm.pri_color < 0 || (*cylinder)->txm.pri_color > 0xFFFFFF)
		return (ft_format_error("Cylinder color is out of range [0,255]"));
	(*cur) = (*cur)->next;
	if (*cur && !ft_check_extra_data(master, cylinder, cur))
		return (false);
	return (true);
}

bool	ft_create_cylinder(t_master **master, t_p_node **cur)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (false);
	(*cur) = (*cur)->next;
	if (!ft_populate_cylinder(master, &cylinder, cur))
		return (free(cylinder), false);
	ft_add_cylinder(master, cylinder);
	return (true);
}
