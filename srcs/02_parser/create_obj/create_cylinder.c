/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:28:42 by malee             #+#    #+#             */
/*   Updated: 2025/02/17 21:11:30 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_add_cylinder(t_master **master, t_cylinder *cylinder)
{
	t_cylinder	*temp;

	temp = (*master)->cylinder_head;
	if (!(*master)->cylinder_head)
		(*master)->cylinder_head = cylinder;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = cylinder;
	}
}

static bool	ft_populate_cylinder(t_master **master, t_cylinder **cylinder,
		t_p_node **cur)
{
	(*cylinder)->cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*cylinder)->cord, -INFINITY, INFINITY,
			"Cylinder coordinates are not a valid vector") || !ft_next(cur,
			"Cylinder has no normal"))
		return (false);
	(*cylinder)->norm = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*cylinder)->norm, -1, 1,
			"Cylinder coordinates are not a valid vector") || !ft_next(cur,
			"Cylinder has no diameter"))
		return (false);
	(*cylinder)->diameter = ft_atod((*cur)->str);
	if (!ft_inrange((*cylinder)->diameter, 0, INFINITY))
		return (ft_error("Cylinder diameter is not a valid double"));
	if (!ft_next(cur, "Cylinder has no height"))
		return (false);
	(*cylinder)->height = ft_atod((*cur)->str);
	if (!ft_inrange((*cylinder)->height, 0, INFINITY))
		return (ft_error("Cylinder height is not a valid double"));
	if (!ft_next(cur, "Cylinder has no color"))
		return (false);
	if (!ft_get_rgb(&(*cylinder)->pro.txm.pri_color, (*cur)->str))
		return (false);
	return (ft_extra_data(master, &((*cylinder)->pro), cur));
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
	printf(GREEN "Cylinder created successfully\n" RESET);
	return (true);
}
