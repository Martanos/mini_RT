/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:38:09 by malee             #+#    #+#             */
/*   Updated: 2025/03/22 00:40:26 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_process_whitespace(t_p_node **head, char **buffer)
{
	if (**buffer && **buffer == '\n')
	{
		if ((*head) && ft_strcmp(ft_last_p_node(*head)->str, "\n")
			&& !ft_add_p_node(head, ft_create_p_node("\n")))
			return (false);
		while (**buffer && **buffer == '\n')
			(*buffer)++;
	}
	else if (**buffer && ft_isspace(**buffer) && **buffer != '\n')
	{
		if ((*head) && !ft_isspace(ft_last_p_node(*head)->str[0])
			&& !ft_add_p_node(head, ft_create_p_node(" ")))
			return (false);
		while (**buffer && ft_isspace(**buffer) && **buffer != '\n')
			(*buffer)++;
	}
	return (true);
}

bool	ft_process_buffer(char *buffer, t_p_node **head)
{
	while (*buffer)
	{
		if (*buffer && *buffer == '#')
			while (*buffer && *buffer != '\n')
				buffer++;
		else if (*buffer && ft_isspace(*buffer))
		{
			if (!ft_process_whitespace(head, &buffer))
				return (false);
		}
		else if (*head && !ft_isspace(ft_last_p_node(*head)->str[0]) && *buffer
			&& !ft_isspace(*buffer) && !ft_add_to_node(head, &buffer))
			return (false);
		else if (*buffer && !ft_add_new_node(head, &buffer))
			return (false);
	}
	return (true);
}
