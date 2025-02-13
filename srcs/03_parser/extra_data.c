/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:10:55 by malee             #+#    #+#             */
/*   Updated: 2025/02/12 17:26:40 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_extra_data(t_master **master, t_obj_pro *pro, t_p_node **cur)
{
	(*cur) = (*cur)->next;
	if ((*cur) && (*cur)->str[0] == '\n')
		return (true);
	while (*cur && (*cur)->str[0] != '\n')
	{
		while (*cur && ft_isspace((*cur)->str[0]) && (*cur)->str[0] != '\n')
			(*cur) = (*cur)->next;
		if (*cur && ft_strncmp((*cur)->str, "txm:", 4) == 0
			&& !ft_add_texture(master, &pro, (*cur)->str + 4))
			return (false);
		else if (*cur && ft_strncmp((*cur)->str, "bpm:", 4) == 0
			&& !ft_add_bump_map(master, &pro, (*cur)->str + 4))
			return (false);
		else if (*cur && ft_strncmp((*cur)->str, "mat:", 4) == 0
			&& !ft_add_material(&pro, (*cur)->str + 4))
			return (false);
		else if (*cur && ft_strncmp((*cur)->str, "txm:", 4) != 0
			&& ft_strncmp((*cur)->str, "bpm:", 4) != 0
			&& ft_strncmp((*cur)->str, "mat:", 4) != 0)
			return (ft_format_error("Unknown object data"));
		if (*cur)
			(*cur) = (*cur)->next;
	}
	return (true);
}
