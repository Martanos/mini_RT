/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:19:49 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 22:39:42 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_populate_material(t_obj_data **obj, char **split, int len)
{
	if (len > 5)
		return (ft_error("Extra data in material"));
	if (len > 0)
		(*obj)->mat.amb = ft_atod(split[0]);
	if (!ft_inrange((*obj)->mat.amb, 0, 1))
		return (ft_error("Ambient is out of range [0,1]"));
	if (len > 1)
		(*obj)->mat.diff = ft_atod(split[1]);
	if (!ft_inrange((*obj)->mat.diff, 0, 1))
		return (ft_error("Diffuse is out of range [0,1]"));
	if (len > 2)
		(*obj)->mat.spec = ft_atod(split[2]);
	if (!ft_inrange((*obj)->mat.spec, 0, 1))
		return (ft_error("Specular is out of range [0,1]"));
	if (len > 3)
		(*obj)->mat.shin = ft_atod(split[3]);
	if (!ft_inrange((*obj)->mat.shin, 0, 200))
		return (ft_error("Shininess is out of range [1,200]"));
	if (len > 4)
		(*obj)->mat.refl = ft_atod(split[4]);
	if (!ft_inrange((*obj)->mat.refl, 0, 1))
		return (ft_error("Reflectivity is out of range [0,1]"));
	return (true);
}

bool	ft_add_material(t_obj_data **obj, char *str)
{
	char	**split;
	int		len;
	bool	result;
	int		i;

	result = false;
	len = 0;
	i = 0;
	split = ft_split(str, ':');
	if (!split)
		return (false);
	while (split[len])
		len++;
	result = ft_populate_material(obj, split, len);
	while (split[i])
		free(split[i++]);
	free(split);
	return (result);
}
