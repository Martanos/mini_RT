/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_strings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:50:53 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 17:10:58 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*ft_construct_str(t_f_node *head)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	while (head && !ft_isspace(head->val))
	{
		temp = ft_strjoin(str, head->val);
		free(str);
		str = ft_strdup(temp);
		free(temp);
		head = head->next;
	}
	return (str);
}

t_p_node	*ft_reconstruct_strings(t_f_node *head)
{
	char		*str;
	t_p_node	*new_list;
	t_p_node	*current;

	new_list = NULL;
	current = new_list;
	while (head && ft_isspace(head->val))
		head = head->next;
	while (head)
	{
		str = ft_construct_str(head);
		if (str)
		{
			ft_add_p_node(&current, ft_create_p_node(str));
			free(str);
		}
		if (head)
		{
			if (head->val == '\n')
				ft_add_p_node(&current, ft_create_p_node("\n"));
			head = head->next;
		}
	}
	return (new_list);
}
