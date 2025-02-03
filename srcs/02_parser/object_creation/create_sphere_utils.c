/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:03:05 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 20:07:56 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_add_populate_material(t_sphere **sphere, char **split)
{
	if (split && split[0])
		(*sphere)->mat.amb = ft_atod(split[0]);
	if (!ft_inrange((*sphere)->mat.amb, 0, 1))
		return (ft_format_error("Ambient is out of range [0,1]"));
	if (split && split[1])
		(*sphere)->mat.diff = ft_atod(split[1]);
	if (!ft_inrange((*sphere)->mat.diff, 0, 1))
		return (ft_format_error("Diffuse is out of range [0,1]"));
	if (split && split[2])
		(*sphere)->mat.spec = ft_atod(split[2]);
	if (!ft_inrange((*sphere)->mat.spec, 0, 1))
		return (ft_format_error("Specular is out of range [0,1]"));
	if (split && split[3])
		(*sphere)->mat.shin = ft_atod(split[3]);
	if (!ft_inrange((*sphere)->mat.shin, 0, 1))
		return (ft_format_error("Shininess is out of range [0,1]"));
	if (split && split[4])
		(*sphere)->mat.refl = ft_atod(split[4]);
	if (!ft_inrange((*sphere)->mat.refl, 0, 1))
		return (ft_format_error("Reflectivity is out of range [0,1]"));
	return (true);
}

bool	ft_add_sphere_material(t_sphere **sphere, char *str)
{
	char	**split;
	bool	result;

	result = false;
	split = ft_split(str, ',');
	if (!split)
		return (false);
	result = ft_add_material_2(sphere, split);
	while (*split)
		free(*split++);
	free(split);
	return (result);
}

static bool	ft_add_populate_texture(t_master **master, t_sphere **sphere,
		char **split)
{
	if (split && split[0])
		(*sphere)->txm.type = ft_atoi(split[0]);
	if ((*sphere)->txm.type > 1 || (*sphere)->txm.type < 0)
		return (ft_format_error("Unknown texture type"));
	if (split && split[1])
		(*sphere)->txm.scale = ft_atod(split[1]);
	if (!ft_inrange((*sphere)->txm.scale, 0, 1))
		return (ft_format_error("Texture scale is out of range [0,1]"));
	if (split && split[2])
		(*sphere)->txm.sec_color = ft_get_rgb(split[3]);
	if (!ft_inrange((*sphere)->txm.sec_color, 0, 0xFFFFFF))
		return (ft_format_error("Secondary color is out of range [0,255]"));
	if (split && split[3])
		(*sphere)->txm.texture_data = mlx_xpm_file_to_image((*master)->mlx_ptr,
				split[3], &(*sphere)->txm.width, &(*sphere)->txm.height);
	if (!(*sphere)->txm.texture_data)
		return (ft_format_error("Failed to load texture"));
	return (true);
}

bool	ft_add_sphere_texture(t_master **master, t_sphere **sphere, char *str)
{
	char	**split;
	bool	result;

	result = false;
	split = ft_split(str, ',');
	if (!split)
		return (false);
	result = ft_add_populate_texture(master, sphere, split);
	while (*split)
		free(*split++);
	free(split);
	return (result);
}

bool	ft_add_sphere_bump_map(t_master **master, t_sphere *sphere, char *str)
{
	sphere->bpm.enabled = true;
	sphere->bpm.map = mlx_xpm_file_to_image((*master)->mlx_ptr, str,
			&sphere->bpm.width, &sphere->bpm.height);
	if (!sphere->bpm.map)
		return (ft_format_error("Failed to load bump map"));
	return (true);
}
