/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cone_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:55:11 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 20:57:04 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_populate_cone_material(t_cone **cone, char **split)
{
	if (split && split[0])
		(*cone)->mat.amb = ft_atod(split[0]);
	if (!ft_inrange((*cone)->mat.amb, 0, 1))
		return (ft_format_error("Ambient is out of range [0,1]"));
	if (split && split[1])
		(*cone)->mat.diff = ft_atod(split[1]);
	if (!ft_inrange((*cone)->mat.diff, 0, 1))
		return (ft_format_error("Diffuse is out of range [0,1]"));
	if (split && split[2])
		(*cone)->mat.spec = ft_atod(split[2]);
	if (!ft_inrange((*cone)->mat.spec, 0, 1))
		return (ft_format_error("Specular is out of range [0,1]"));
	if (split && split[3])
		(*cone)->mat.shin = ft_atod(split[3]);
	if (!ft_inrange((*cone)->mat.shin, 0, 1))
		return (ft_format_error("Shininess is out of range [0,1]"));
	if (split && split[4])
		(*cone)->mat.refl = ft_atod(split[4]);
	if (!ft_inrange((*cone)->mat.refl, 0, 1))
		return (ft_format_error("Reflectivity is out of range [0,1]"));
	return (true);
}

bool	ft_add_cone_material(t_cone **cone, char *str)
{
	char	**split;
	bool	result;

	result = false;
	split = ft_split(str, ',');
	if (!split)
		return (false);
	result = ft_populate_cone_material(cone, split);
	while (*split)
		free(*split++);
	free(split);
	return (result);
}

static bool	ft_populate_cone_texture(t_master **master, t_cone **cone,
		char **split)
{
	if (split && split[0])
		(*cone)->txm.type = ft_atoi(split[0]);
	if ((*cone)->txm.type > 1 || (*cone)->txm.type < 0)
		return (ft_format_error("Unknown texture type"));
	if (split && split[1])
		(*cone)->txm.scale = ft_atod(split[1]);
	if (!ft_inrange((*cone)->txm.scale, 0, 1))
		return (ft_format_error("Texture scale is out of range [0,1]"));
	if (split && split[2])
		(*cone)->txm.sec_color = ft_get_rgb(split[3]);
	if (!ft_inrange((*cone)->txm.sec_color, 0, 0xFFFFFF))
		return (ft_format_error("Secondary color is out of range [0,255]"));
	if (split && split[3])
		(*cone)->txm.texture_data = mlx_xpm_file_to_image((*master)->mlx_ptr,
				split[3], &(*cone)->txm.width, &(*cone)->txm.height);
	if (!(*cone)->txm.texture_data)
		return (ft_format_error("Failed to load texture"));
	return (true);
}

bool	ft_add_cone_texture(t_master **master, t_cone **cone, char *str)
{
	char	**split;
	bool	result;

	result = false;
	split = ft_split(str, ',');
	if (!split)
		return (false);
	result = ft_populate_cone_texture(master, cone, split);
	while (*split)
		free(*split++);
	free(split);
	return (result);
}

bool	ft_add_cone_bump_map(t_master **master, t_cone *cone, char *str)
{
	cone->bpm.enabled = true;
	cone->bpm.map = mlx_xpm_file_to_image((*master)->mlx_ptr, str,
			&cone->bpm.width, &cone->bpm.height);
	if (!cone->bpm.map)
		return (ft_format_error("Failed to load bump map"));
	return (true);
}
