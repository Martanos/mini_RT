/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:10:55 by malee             #+#    #+#             */
/*   Updated: 2025/02/05 19:53:36 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_extra_data(t_master **master, t_obj_pro **pro, t_p_node **cur)
{
	(*cur) = (*cur)->next;
	if ((*cur) && (*cur)->str[0] == '\n')
		return (true);
	while (*cur && (*cur)->str[0] != '\n')
	{
		if (ft_strcmp((*cur)->str, "txm:") == 0 && !ft_add_texture(master, pro,
				(*cur)->str + 4))
			return (false);
		else if (ft_strcmp((*cur)->str, "bpm:") == 0 && !ft_add_bump_map(master,
				pro, (*cur)->str + 4))
			return (false);
		else if (ft_strcmp((*cur)->str, "mat:") == 0 && !ft_add_material(pro,
				(*cur)->str + 4))
			return (false);
		else
			return (ft_format_error("Unknown object data"));
		(*cur) = (*cur)->next;
	}
	return (true);
}
