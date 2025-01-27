/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_amb_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:13:53 by malee             #+#    #+#             */
/*   Updated: 2025/01/27 11:57:52 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	ft_create_amb(t_master **master, t_p_node **cur)
{
	if ((*master)->amb_head)
	{
		ft_format_error(cur, "Ambient light already exists");
		return (true);
	}
	while (*cur && (*cur)->val == ' ')
		(*cur) = (*cur)->next;
	(*master)->amb_head->ratio = ft_atod(cur);
	if (!ft_inrange((*master)->amb_head->ratio, 0, 1))
	{
		ft_format_error(cur, "Ambient light ratio must be between 0 and 1");
		return (true);
	}
	(*master)->amb_head->rgb = ft_atod(cur);
}
