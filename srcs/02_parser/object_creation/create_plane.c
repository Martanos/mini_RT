/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:10:18 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 20:21:26 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_add_plane(t_master **master, t_plane *plane)
{
	t_sphere	*temp;

	temp = (*master)->plane_head;
	if (!(*master)->plane_head)
		(*master)->plane_head = plane;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = plane;
	}
}

static bool	ft_check_extra_data(t_master **master, t_plane **plane,
		t_p_node **cur)
{
	while (*cur)
	{
		if (ft_strcmp((*cur)->str, "txm:") == 0)
		{
			if (!ft_add_plane_texture(master, plane, (*cur)->str + 4))
				return (false);
		}
		else if (ft_strcmp((*cur)->str, "bpm:") == 0)
		{
			if (!ft_add_plane_bump_map(master, plane, (*cur)->str + 4))
				return (false);
		}
		else if (ft_strcmp((*cur)->str, "mat:"))
		{
			if (!ft_add_plane_material(plane, (*cur)->str + 4))
				return (false);
		}
		else
			return (ft_format_error("Unknown plane data"));
		(*cur) = (*cur)->next;
	}
	return (true);
}

static bool	ft_populate_plane(t_master **master, t_plane **plane,
		t_p_node **cur)
{
	(*plane)->cord = ft_get_xyz(cur);
	if (!ft_inrange((*plane)->cord.x, -INFINITY, INFINITY)
		|| !ft_inrange((*plane)->cord.y, -INFINITY, INFINITY)
		|| !ft_inrange((*plane)->cord.z, -INFINITY, INFINITY))
		return (ft_format_error("Plane coordinates are not a valid vector"));
	(*cur) = (*cur)->next;
	(*plane)->norm = ft_get_xyz(cur);
	if (!ft_inrange((*plane)->norm.x, -1, 1) || !ft_inrange((*plane)->norm.y,
			-1, 1) || !ft_inrange((*plane)->norm.z, -1, 1))
		return (ft_format_error("Plane coordinates are not a valid vector"));
	(*cur) = (*cur)->next;
	(*plane)->txm.pri_color = ft_get_rgb((*cur)->str);
	if ((*plane)->txm.pri_color < 0 || (*plane)->txm.pri_color > 0xFFFFFF)
		return (ft_format_error("Plane color is out of range [0,255]"));
	(*cur) = (*cur)->next;
	if (*cur && !ft_check_extra_data(master, plane, cur))
		return (false);
	return (true);
}

// @brief Creates a plane object
// @param master pointer to the master structure
// @param cur pointer to the current node in the parser node list
// @return true if successful, false if error
bool	ft_create_plane(t_master **master, t_p_node **cur)
{
	t_plane	*plane;

	plane = (t_plane *)ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (false);
	(*cur) = (*cur)->next;
	if (!ft_populate_plane(master, &plane, cur))
		return (free(plane), false);
	ft_add_plane(master, plane);
	return (true);
}
