/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:49:58 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 11:38:41 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_inrange(double value, double min, double max)
{
	return (value >= min && value <= max);
}

void	ft_skip_spaces(t_p_node **cur)
{
	while (*cur && ft_isspace((*cur)->val))
		(*cur) = (*cur)->next;
}
