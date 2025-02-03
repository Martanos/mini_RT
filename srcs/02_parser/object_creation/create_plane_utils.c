/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_plane_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:22:45 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 20:27:40 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_populate_plane_material(t_plane **plane, char **split)
{
	if (split && split[0])
		(*plane)->mat.amb = ft_atod(split[0]);
	if (!ft_inrange((*plane)->mat.amb, 0, 1))
		return (ft_format_error("Ambient is out of range [0,1]"));
	if (split && split[1])
		(*plane)->mat.diff = ft_atod(split[1]);
	if (!ft_inrange((*plane)->mat.diff, 0, 1))
		return (ft_format_error("Diffuse is out of range [0,1]"));
	if (split && split[2])
		(*plane)->mat.spec = ft_atod(split[2]);
	if (!ft_inrange((*plane)->mat.spec, 0, 1))
		return (ft_format_error("Specular is out of range [0,1]"));
	if (split && split[3])
		(*plane)->mat.shin = ft_atod(split[3]);
	if (!ft_inrange((*plane)->mat.shin, 0, 1))
		return (ft_format_error("Shininess is out of range [0,1]"));
	if (split && split[4])
		(*plane)->mat.refl = ft_atod(split[4]);
	if (!ft_inrange((*plane)->mat.refl, 0, 1))
		return (ft_format_error("Reflectivity is out of range [0,1]"));
	return (true);
}

bool	ft_add_plane_material(t_plane **plane, char *str)
{
	char	**split;
	bool	result;

	result = false;
	split = ft_split(str, ',');
	if (!split)
		return (false);
	result = ft_populate_plane_material(plane, split);
	while (*split)
		free(*split++);
	free(split);
	return (result);
}

static bool	ft_populate_plane_texture(t_master **master, t_plane **plane,
		char **split)
{
	if (split && split[0])
		(*plane)->txm.type = ft_atoi(split[0]);
	if ((*plane)->txm.type > 1 || (*plane)->txm.type < 0)
		return (ft_format_error("Unknown texture type"));
	if (split && split[1])
		(*plane)->txm.scale = ft_atod(split[1]);
	if (!ft_inrange((*plane)->txm.scale, 0, 1))
		return (ft_format_error("Texture scale is out of range [0,1]"));
	if (split && split[2])
		(*plane)->txm.sec_color = ft_get_rgb(split[3]);
	if (!ft_inrange((*plane)->txm.sec_color, 0, 0xFFFFFF))
		return (ft_format_error("Secondary color is out of range [0,255]"));
	if (split && split[3])
		(*plane)->txm.texture_data = mlx_xpm_file_to_image((*master)->mlx_ptr,
				split[3], &(*plane)->txm.width, &(*plane)->txm.height);
	if (!(*plane)->txm.texture_data)
		return (ft_format_error("Failed to load texture"));
	return (true);
}

bool	ft_add_plane_texture(t_master **master, t_plane **plane, char *str)
{
	char	**split;
	bool	result;

	result = false;
	split = ft_split(str, ',');
	if (!split)
		return (false);
	result = ft_add_populate_texture(master, plane, split);
	while (*split)
		free(*split++);
	free(split);
	return (result);
}

bool	ft_add_plane_bump_map(t_master **master, t_plane *plane, char *str)
{
	plane->bpm.enabled = true;
	plane->bpm.map = mlx_xpm_file_to_image((*master)->mlx_ptr, str,
			&plane->bpm.width, &plane->bpm.height);
	if (!plane->bpm.map)
		return (ft_format_error("Failed to load bump map"));
	return (true);
}
