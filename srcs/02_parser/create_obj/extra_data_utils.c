/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_data_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:55:11 by malee             #+#    #+#             */
/*   Updated: 2025/02/17 19:08:25 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_populate_material(t_obj_pro **pro, char **split, int len)
{
	if (len > 5)
		return (ft_error("Extra data in material"));
	if (len < 4)
		return (ft_error("Material data is incomplete"));
	if (len > 0)
		(*pro)->mat.amb = ft_atod(split[0]);
	if (!ft_inrange((*pro)->mat.amb, 0, 1))
		return (ft_error("Ambient is out of range [0,1]"));
	if (len > 1)
		(*pro)->mat.diff = ft_atod(split[1]);
	if (!ft_inrange((*pro)->mat.diff, 0, 1))
		return (ft_error("Diffuse is out of range [0,1]"));
	if (len > 2)
		(*pro)->mat.spec = ft_atod(split[2]);
	if (!ft_inrange((*pro)->mat.spec, 0, 1))
		return (ft_error("Specular is out of range [0,1]"));
	if (len > 3)
		(*pro)->mat.shin = ft_atod(split[3]);
	if (!ft_inrange((*pro)->mat.shin, 0, 200))
		return (ft_error("Shininess is out of range [1,200]"));
	if (len > 4)
		(*pro)->mat.refl = ft_atod(split[4]);
	if (!ft_inrange((*pro)->mat.refl, 0, 1))
		return (ft_error("Reflectivity is out of range [0,1]"));
	return (true);
}

bool	ft_add_material(t_obj_pro **pro, char *str)
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
	result = ft_populate_material(pro, split, len);
	while (split[i])
		free(split[i++]);
	free(split);
	return (result);
}

static bool	ft_populate_texture(t_master **master, t_obj_pro **pro,
		char **split, int len)
{
	if (len > 4)
		return (ft_error("Extra data in texture"));
	if (len < 4)
		return (ft_error("Texture data is incomplete"));
	if (len > 0)
		(*pro)->txm.type = ft_atoi(split[0]);
	if ((*pro)->txm.type > 2 || (*pro)->txm.type < 0)
		return (ft_error("Unknown texture type"));
	if (len > 1)
		(*pro)->txm.scale = ft_atod(split[1]);
	if (!ft_inrange((*pro)->txm.scale, 0, 1))
		return (ft_error("Texture scale is out of range [0,1]"));
	if (len > 2)
		if (split[2] && !ft_get_rgb(&(*pro)->txm.sec_color, split[2]))
			return (false);
	if (len > 3)
		(*pro)->txm.img = mlx_xpm_file_to_image((*master)->mlx_ptr, split[3],
				&(*pro)->txm.width, &(*pro)->txm.height);
	if (!(*pro)->txm.img)
		return (ft_error("Failed to load texture"));
	return (true);
}

bool	ft_add_texture(t_master **master, t_obj_pro **pro, char *str)
{
	char	**split;
	char	**original;
	bool	result;
	int		len;

	result = false;
	len = 0;
	split = ft_split(str, ':');
	if (!split)
		return (false);
	while (split[len])
		len++;
	result = ft_populate_texture(master, pro, split, len);
	original = split;
	while (*split)
		free(*split++);
	free(original);
	return (result);
}

bool	ft_add_bump_map(t_master **master, t_obj_pro **pro, char *str)
{
	if (!str)
		return (ft_error("No bump map data specified"));
	(*pro)->bpm.enabled = true;
	(*pro)->bpm.map = mlx_xpm_file_to_image((*master)->mlx_ptr, str,
			&(*pro)->bpm.width, &(*pro)->bpm.height);
	if (!(*pro)->bpm.map)
		return (ft_error("Failed to load bump map"));
	return (true);
}
