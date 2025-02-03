/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_amb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:13:53 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 17:24:31 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	ft_create_amb(t_master **master, t_p_node **cur)
{
	if ((*master)->amb_head.set)
		return (ft_format_error("Ambient light already exists"));
	else
		(*master)->amb_head.set = true;
	if ((*cur)->next == NULL)
		return (ft_format_error("Empty ambient light found"));
	(*master)->amb_head.ratio = ft_atod(cur);
	if (isnan((*master)->amb_head.ratio)
		|| !ft_inrange((*master)->amb_head.ratio, 0, 1))
		return (ft_format_error("Ambient light ratio must be between 0 and 1"));
	(*master)->amb_head.rgb = ft_get_rgb(cur);
	if ((*master)->amb_head.rgb == -1)
		return (ft_format_error("Invalid RGB value"));
	ft_skip_spaces(cur);
	if (*cur)
		return (ft_format_error("Ambient light has extra data"));
	return (false);
}
