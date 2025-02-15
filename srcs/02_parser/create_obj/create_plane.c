/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:10:18 by malee             #+#    #+#             */
/*   Updated: 2025/02/12 16:34:52 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_add_plane(t_master **master, t_plane *plane)
{
	t_plane	*temp;

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

static bool	ft_populate_plane(t_master **master, t_plane **plane,
		t_p_node **cur)
{
	if (!ft_next(cur, "Plane has no coordinates"))
		return (false);
	(*plane)->cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*plane)->cord, -INFINITY, INFINITY,
			"Plane coordinates are not a valid vector") || !ft_next(cur,
			"Plane has no normal"))
		return (false);
	(*plane)->norm = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*plane)->norm, -1, 1,
			"Plane coordinates are not a valid vector") || !ft_next(cur,
			"Plane has no color"))
		return (false);
	if (!ft_get_rgb(&(*plane)->pro.txm.pri_color, (*cur)->str))
		return (false);
	return (ft_extra_data(master, &((*plane)->pro), cur));
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
	if (!ft_populate_plane(master, &plane, cur))
		return (free(plane), false);
	ft_add_plane(master, plane);
	printf(GREEN "Plane created successfully\n" RESET);
	return (true);
}
