/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cylinder_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:28:30 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 20:44:39 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_populate_cylinder_material(t_cylinder **cylinder, char **split)
{
	if (split && split[0])
		(*cylinder)->mat.amb = ft_atod(split[0]);
	if (!ft_inrange((*cylinder)->mat.amb, 0, 1))
		return (ft_format_error("Ambient is out of range [0,1]"));
	if (split && split[1])
		(*cylinder)->mat.diff = ft_atod(split[1]);
	if (!ft_inrange((*cylinder)->mat.diff, 0, 1))
		return (ft_format_error("Diffuse is out of range [0,1]"));
	if (split && split[2])
		(*cylinder)->mat.spec = ft_atod(split[2]);
	if (!ft_inrange((*cylinder)->mat.spec, 0, 1))
		return (ft_format_error("Specular is out of range [0,1]"));
	if (split && split[3])
		(*cylinder)->mat.shin = ft_atod(split[3]);
	if (!ft_inrange((*cylinder)->mat.shin, 0, 1))
		return (ft_format_error("Shininess is out of range [0,1]"));
	if (split && split[4])
		(*cylinder)->mat.refl = ft_atod(split[4]);
	if (!ft_inrange((*cylinder)->mat.refl, 0, 1))
		return (ft_format_error("Reflectivity is out of range [0,1]"));
	return (true);
}

bool	ft_add_cylinder_material(t_cylinder **cylinder, char *str)
{
	char	**split;
	bool	result;

	result = false;
	split = ft_split(str, ',');
	if (!split)
		return (false);
	result = ft_populate_cylinder_material(cylinder, split);
	while (*split)
		free(*split++);
	free(split);
	return (result);
}

static bool	ft_populate_cylinder_texture(t_master **master,
		t_cylinder **cylinder, char **split)
{
	if (split && split[0])
		(*cylinder)->txm.type = ft_atoi(split[0]);
	if ((*cylinder)->txm.type > 1 || (*cylinder)->txm.type < 0)
		return (ft_format_error("Unknown texture type"));
	if (split && split[1])
		(*cylinder)->txm.scale = ft_atod(split[1]);
	if (!ft_inrange((*cylinder)->txm.scale, 0, 1))
		return (ft_format_error("Texture scale is out of range [0,1]"));
	if (split && split[2])
		(*cylinder)->txm.sec_color = ft_get_rgb(split[3]);
	if (!ft_inrange((*cylinder)->txm.sec_color, 0, 0xFFFFFF))
		return (ft_format_error("Secondary color is out of range [0,255]"));
	if (split && split[3])
		(*cylinder)->txm.texture_data = mlx_xpm_file_to_image((*master)->mlx_ptr,
				split[3], &(*cylinder)->txm.width, &(*cylinder)->txm.height);
	if (!(*cylinder)->txm.texture_data)
		return (ft_format_error("Failed to load texture"));
	return (true);
}

bool	ft_add_cylinder_texture(t_master **master, t_cylinder **cylinder,
		char *str)
{
	char	**split;
	bool	result;

	result = false;
	split = ft_split(str, ',');
	if (!split)
		return (false);
	result = ft_populate_cylinder_texture(master, cylinder, split);
	while (*split)
		free(*split++);
	free(split);
	return (result);
}

bool	ft_add_cylinder_bump_map(t_master **master, t_cylinder *cylinder,
		char *str)
{
	cylinder->bpm.enabled = true;
	cylinder->bpm.map = mlx_xpm_file_to_image((*master)->mlx_ptr, str,
			&cylinder->bpm.width, &cylinder->bpm.height);
	if (!cylinder->bpm.map)
		return (ft_format_error("Failed to load bump map"));
	return (true);
}
