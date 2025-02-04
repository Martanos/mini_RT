/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_xyz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:36:26 by malee             #+#    #+#             */
/*   Updated: 2025/02/04 17:07:59 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vect	ft_get_xyz(t_p_node **cur)
{
	t_vect	xyz;
	char	**split;

	ft_bzero(&xyz, sizeof(t_vect));
	split = ft_split((*cur)->str, ',');
	if (split == NULL)
		return (xyz);
	if (split && split[0] && split[1] && split[2])
	{
		xyz.x = ft_atod(split[0]);
		xyz.y = ft_atod(split[1]);
		xyz.z = ft_atod(split[2]);
	}
	while (split && *split)
	{
		free(*split);
		split++;
	}
	free(split);
	return (xyz);
}
