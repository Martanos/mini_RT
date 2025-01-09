/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 19:42:25 by malee             #+#    #+#             */
/*   Updated: 2025/01/09 19:18:18 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
		if (cur->type == PARSER_TYPE_RGB_VAL)
			ft_str_to_rgb(cur);
		else if (cur->type == PARSER_TYPE_L_RATIO
			|| cur->type == PARSER_TYPE_HEIGHT
			|| cur->type == PARSER_TYPE_DIAMETER
			|| cur->type == PARSER_TYPE_COORD || cur->type == PARSER_TYPE_FOV)
			ft_str_to_dbl(cur);
		cur = cur->next;
	}
}
