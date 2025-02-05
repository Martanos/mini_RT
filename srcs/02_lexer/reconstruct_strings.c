/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reconstruct_strings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:50:53 by malee             #+#    #+#             */
/*   Updated: 2025/02/05 19:36:53 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*ft_construct_str(t_f_node **head)
{
	char	*str;
	char	*temp;
	char	*holder;

	str = ft_strdup("");
	holder = (char *)ft_calloc(2, sizeof(char));
	while (head && !ft_isspace((*head)->val))
	{
		holder[0] = (*head)->val;
		temp = ft_strjoin(str, holder);
		free(str);
		str = ft_strdup(temp);
		free(temp);
		(*head) = (*head)->next;
	}
	free(holder);
	return (str);
}

t_p_node	*ft_reconstruct_strings(t_f_node *head)
{
	char		*str;
	t_p_node	*new_list;

	new_list = NULL;
	while (head)
	{
		while (head && ft_isspace(head->val))
			head = head->next;
		str = ft_construct_str(&head);
		if (str)
		{
			ft_add_p_node(&new_list, ft_create_p_node(str));
			free(str);
		}
		if (head)
		{
			if (head->val == '\n')
				ft_add_p_node(&new_list, ft_create_p_node("\n"));
			head = head->next;
		}
	}
	return (new_list);
}
