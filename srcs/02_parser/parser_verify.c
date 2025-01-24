/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_verify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:52:02 by malee             #+#    #+#             */
/*   Updated: 2025/01/24 07:15:15 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_skip_whitespace(t_p_node **head)
{
	while (head && ft_isspace(head->val))
		head = head->next;
}

/*
** @brief Verifies the syntax of the file fatal error if syntax is incorrect
** @param head pointer to the head of the list
*/
bool	ft_verify(t_p_node *head)
{
	while (head)
	{
		// skip whitespace
		// skip comments
		if (head->val == 'A')
			ft_add_id(&id_list, head->val);
		head = head->next;
	}
}

void	ft_verify_amb(t_p_node *head)
{
}

void	ft_verify_cam(t_p_node *head)
{
}

void	ft_verify_light(t_p_node *head)
{
}

void	ft_verify_sphere(t_p_node *head)
{
}

void	ft_verify_plane(t_p_node *head)
{
}

void	ft_verify_cylinder(t_p_node *head)
{
}

void	ft_verify_cone(t_p_node *head)
{
}
