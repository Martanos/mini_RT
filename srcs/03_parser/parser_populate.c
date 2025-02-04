/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_populate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:30:00 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 20:57:37 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_identify(t_master **master, t_p_node **cur)
{
	if (ft_strcmp((*cur)->str, "A") == 0)
		return (ft_create_amb(master, cur));
	else if (ft_strcmp((*cur)->str, "C") == 0)
		return (ft_create_cam(master, cur));
	else if (ft_strcmp((*cur)->str, "L") == 0)
		return (ft_create_light(master, cur));
	else if (ft_strcmp((*cur)->str, "pl") == 0)
		return (ft_create_plane(master, cur));
	else if (ft_strcmp((*cur)->str, "cy") == 0)
		return (ft_create_cylinder(master, cur));
	else if (ft_strcmp((*cur)->str, "sp") == 0)
		return (ft_create_sphere(master, cur));
	else if (ft_strcmp((*cur)->str, "co") == 0)
		return (ft_create_cone(master, cur));
	return (ft_format_error("Invalid identifier"));
}
/*
** @brief Returns a master structure with the parsed data
** @param head pointer to the head of the parser node list
** @return false if successful, true if error
*/
t_master	*ft_populate(t_p_node *cur)
{
	t_master	*master;

	master = (t_master *)ft_calloc(1, sizeof(t_master));
	while (cur)
	{
		if (!ft_identify(&master, &cur))
			return (ft_free_master(master), NULL);
		if (cur)
			cur = cur->next;
	}
	return (master);
}
