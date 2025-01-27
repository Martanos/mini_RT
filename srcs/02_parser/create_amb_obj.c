/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_amb_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:13:53 by malee             #+#    #+#             */
/*   Updated: 2025/01/27 15:23:35 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	ft_create_amb(t_master **master, t_p_node **cur)
{
	bool	error;

	error = false;
	if ((*master)->amb_head)
		error = ft_format_error(cur, "Ambient light already exists");
	(*master)->amb_head->ratio = ft_atod(cur);
	if (!ft_inrange((*master)->amb_head->ratio, 0, 1))
		error = ft_format_error(cur,
				"Ambient light ratio must be between 0 and 1");
	(*master)->amb_head->rgb = ft_get_rgb(cur);
	if ((*master)->amb_head->rgb == -1)
		return (true);
	while (*cur && !ft_isspace((*cur)->val))
		(*cur) = (*cur)->next;
	return (error);
}
