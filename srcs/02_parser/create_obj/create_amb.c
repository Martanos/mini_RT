/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_amb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:13:53 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 22:13:12 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	ft_create_amb(t_scene **scene, t_p_node **cur)
{
	if ((*scene)->amb_data.set)
		return (ft_error("Ambient light already exists"));
	else
		(*scene)->amb_data.set = true;
	if (!ft_next(cur, "Ambient light has no ratio"))
		return (ft_error("Ambient light has no ratio"));
	(*scene)->amb_data.ratio = ft_atod((*cur)->str);
	if (!ft_inrange((*scene)->amb_data.ratio, 0, 1))
		return (ft_error("Ambient light ratio must be between 0 and 1"));
	if (!ft_next(cur, "Ambient light has no RGB value"))
		return (false);
	if (!ft_get_rgb(&(*scene)->amb_data.rgb, (*cur)->str))
		return (false);
	(*cur) = (*cur)->next;
	if ((*cur) && (*cur)->str != NULL && (*cur)->str[0] != '\n')
		return (ft_error("Ambient light has extra data"));
	printf(GREEN "Ambient light created successfully\n" RESET);
	return (true);
}
