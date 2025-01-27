/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_populate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:30:00 by malee             #+#    #+#             */
/*   Updated: 2025/01/24 08:27:01 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

char	*ft_get_id(t_p_node **head)
{
	char	*id;

	id = ft_strdup("");
	while ((*head) && (*head)->val && !ft_isspace((*head)->val[0]))
	{
		id = ft_strjoin(id, (*head)->val);
		(*head) = (*head)->next;
	}
	return (id);
}

void	ft_parse_id(t_master *master, t_p_node *head, bool *error, char *id)
{
	if (id && ft_strcmp(id, "A") == 0)
		master->amb_head = ft_create_amb(head, &error);
	else if (id && ft_strcmp(id, "C") == 0)
		master->cam_head = ft_create_cam(head, &error);
	else if (id && ft_strcmp(id, "L") == 0)
		master->light_head = ft_create_light(head, &error);
	else if (id && ft_strcmp(id, "pl") == 0)
		master->plane_head = ft_create_plane(head, &error);
	else if (id && ft_strcmp(id, "cy") == 0)
		master->cylinder_head = ft_create_cylinder(head, &error);
	else if (id && ft_strcmp(id, "sp") == 0)
		master->sphere_head = ft_create_sphere(head, &error);
	else
		ft_format_error(head, "Invalid identifier", error);
}
/*
** @brief Populates the master structure with the parsed data
** @param master pointer to the master structure
** @param head pointer to the head of the parser node list
** @return false if successful, true if error
*/
bool	ft_populate(t_master *master, t_p_node *head)
{
	bool	error;
	char	*id;

	error = false;
	id = NULL;
	while (head)
	{
		id = ft_get_id(&head);
		ft_parse_id(master, head, &error, id);
		free(id);
		head = head->next;
	}
	if (error)
		ft_free_master(master);
	return (error);
}
