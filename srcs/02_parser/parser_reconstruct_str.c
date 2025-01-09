/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reconstruct_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:45:14 by malee             #+#    #+#             */
/*   Updated: 2025/01/09 13:30:13 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_skip_whitespace(t_parser_node **cur, t_parser_node **new_head)
{
	while ((*cur) && ft_is_space((*cur)->str[0]))
	{
		if ((*cur)->str[0] == '\n')
			ft_add_parser_node(new_head,
				ft_create_parser_node(PARSER_TYPE_NEW_LINE, '\n', 0, NULL));
		(*cur) = (*cur)->next;
	}
}

static void	ft_skip_comment(t_parser_node **cur, t_parser_node **new_head)
{
	if ((*cur)->str[0] == '#')
		while ((*cur) && (*cur)->str[0] != '\n')
			(*cur) = (*cur)->next;
}

static void	ft_reconstruct_str(t_parser_node **cur, t_parser_node **new_head)
{
	t_parser_node	*pos_start;
	char			*str_content;
	size_t			i;

	if (!cur || !*cur)
		return ;
	pos_start = (*cur);
	i = 0;
	while ((*cur) && !ft_is_space((*cur)->str[0]) && (*cur)->str[0] != '#')
	{
		i++;
		(*cur) = (*cur)->next;
	}
	str_content = (char *)ft_calloc(i + 1, sizeof(char));
	if (!str_content)
		return ;
	i = 0;
	while (pos_start && pos_start != *cur)
	{
		str_content[i++] = pos_start->str[0];
		pos_start = pos_start->next;
	}
	ft_add_parser_node(new_head, ft_create_parser_node(PARSER_TYPE_NONE,
			str_content, 0, NULL));
	free(str_content);
}

/*
** @brief Reconstructs strings from parser node list, returns a new list
** @param head pointer to the head of the list
** @return pointer to the head of the new list
*/
void	ft_reconstructor(t_parser_node **head)
{
	t_parser_node	*new_head;
	t_parser_node	*cur;

	cur = *head;
	new_head = NULL;
	while (cur)
	{
		ft_skip_whitespace(&cur, &new_head);
		ft_skip_comment(&cur, &new_head);
		ft_reconstruct_str(&cur, &new_head);
	}
	ft_free_parser_list(*head);
	*head = new_head;
}
