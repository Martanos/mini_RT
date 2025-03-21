/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_xyz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:36:26 by malee             #+#    #+#             */
/*   Updated: 2025/03/21 23:51:54 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vect	ft_get_xyz(t_p_node **cur)
{
	t_vect	xyz;
	char	**split;
	char	**original;

	ft_bzero(&xyz, sizeof(t_vect));
	split = ft_split((*cur)->str, ',');
	if (split == NULL)
		return (xyz);
	original = split;
	if (!split[0] || !split[1] || !split[2])
	{
		while (*split)
			free(*split++);
		free(original);
		return (ft_vect_create(NAN, NAN, NAN));
	}
	xyz = ft_vect_create(ft_atod(split[0]), ft_atod(split[1]),
			ft_atod(split[2]));
	while (*split)
		free(*split++);
	free(original);
	return (xyz);
}
