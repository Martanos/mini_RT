/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_populate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:30:00 by malee             #+#    #+#             */
/*   Updated: 2025/01/27 15:23:09 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static char	*ft_get_id(t_p_node **head)
{
	char	*id;
	char	*new_id;

	id = ft_strdup("");
	while (*head && !ft_isspace((*head)->val))
	{
		new_id = ft_strjoin(id, (*head)->val);
		free(id);
		id = ft_strdup(new_id);
		free(new_id);
		(*head) = (*head)->next;
	}
	return (id);
}

void	ft_identify(t_master **master, t_p_node **cur, char *id)
{
	bool	error;

	error = false;
	if (id && ft_strcmp(id, "A") == 0)
		error = ft_create_amb(master, cur);
	else if (id && ft_strcmp(id, "C") == 0)
		error = ft_create_cam(master, cur);
	else if (id && ft_strcmp(id, "L") == 0)
		error = ft_create_light(master, cur);
	else if (id && ft_strcmp(id, "pl") == 0)
		error = ft_create_plane(master, cur);
	else if (id && ft_strcmp(id, "cy") == 0)
		error = ft_create_cylinder(master, cur);
	else if (id && ft_strcmp(id, "sp") == 0)
		error = ft_create_sphere(master, cur);
	else if (id && ft_strcmp(id, "co") == 0)
		error = ft_create_cone(master, cur);
	else
		error = ft_format_error(cur, "Invalid identifier");
	free(id);
	return (error);
}
/*
** @brief Populates the master structure with the parsed data
** @param head pointer to the head of the parser node list
** @return false if successful, true if error
*/
t_master	*ft_populate(t_p_node *cur)
{
	t_master	*master;
	bool		error;

	error = false;
	master = (t_master *)ft_calloc(1, sizeof(t_master));
	while (cur)
	{
		ft_identify(&master, &cur, ft_get_id(&cur));
		if (cur)
			cur = cur->next;
	}
	if (error)
		ft_free_master(master);
	return (error);
}
