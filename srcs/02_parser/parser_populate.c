/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_populate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:30:00 by malee             #+#    #+#             */
/*   Updated: 2025/01/10 22:32:03 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_format_error(t_p_node *head, char *message, bool *error)
{
	*error = true;
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("At line: ", 2);
	ft_putnbr_fd(head->line, 2);
	ft_putstr_fd(" position: ", 2);
	ft_putnbr_fd(head->pos, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(RESET, 2);
	return (false);
}

void	ft_populate(t_master *master, t_p_node *head)
{
	bool	error;

	error = false;
	while (head)
	{
		if (head->val == "A")
			master->amb_head = ft_create_amb(head, &error);
		else if (head->val == "C")
			master->cam_head = ft_create_cam(head, &error);
		else if (head->val == "L")
			master->light_head = ft_create_light(head, &error);
		else if (head->val == "pl")
			master->plane_head = ft_create_plane(head, &error);
		else if (head->val == "cy")
			master->cylinder_head = ft_create_cylinder(head, &error);
		else if (head->val == "sp")
			master->sphere_head = ft_create_sphere(head, &error);
		head = head->down;
	}
	if (error)
	{
		ft_free_master(master);
		return (false);
	}
	return (true);
}
