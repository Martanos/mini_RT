/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:42:25 by malee             #+#    #+#             */
/*   Updated: 2025/01/07 19:47:16 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_str_to_int(t_parser_node *node)
{
}

static bool	ft_str_to_rgb(t_parser_node *node)
{
}

static bool	ft_str_to_dbl(t_parser_node *node)
{
}

bool	ft_type_convert(t_parser_node **head)
{
	t_parser_node	*cur;

	cur = *head;
	while (cur)
	{
		cur = cur->next;
	}
}
