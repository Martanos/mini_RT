/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txm_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:18:36 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 22:37:31 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
** @brief Load a texture from a file
** @note required as mlx_xpm_file_to_image segfaults when given an invalid file
** @param master The master structure
** @param pro The object properties structure
** @param str The path to the texture file
** @return true if the texture is loaded successfully, false otherwise
*/
static bool	ft_load_xpm_texture(t_scene **scene, t_obj_data **obj, char *str)
{
	ssize_t	len;
	int		fd;

	if (!str)
		return (ft_error("No texture data specified"));
	len = ft_strlen(str);
	if (len < 4 || str[len - 1] != 'm' || str[len - 2] != 'p' || str[len
		- 3] != 'x' || str[len - 4] != '.')
		return (ft_error("Invalid file extension expected: .xpm"), false);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_error("Failed to access xpm texture file"), false);
	close(fd);
	(*obj)->txm.img = mlx_xpm_file_to_image((*scene)->mlx_ptr, str,
			&(*obj)->txm.width, &(*obj)->txm.height);
	if (!(*obj)->txm.img)
		return (ft_error("Failed to load xpm texture from file"), false);
	(*obj)->txm.data = (int *)mlx_get_data_addr((*obj)->txm.img,
			&(*obj)->txm.bpp, &(*obj)->txm.line_len, &(*obj)->txm.endian);
	if (!(*obj)->txm.data)
		return (ft_error("Failed to get xpm texture data"), false);
	return (true);
}

static bool	ft_populate_texture(t_scene **scene, t_obj_data **obj, char **split,
		int len)
{
	if (len > 3)
		return (ft_error("Extra data in texture"));
	if (len > 0)
		(*obj)->txm.type = ft_atoi(split[0]);
	if ((*obj)->txm.type < 0 || (*obj)->txm.type > 2)
		return (ft_error("Unknown texture type"));
	if ((*obj)->txm.type == 0 && len > 2)
		return (ft_error("Extra data in texture specified as solid color"));
	if (len > 1)
		(*obj)->txm.scale = ft_atod(split[1]);
	if (!ft_inrange((*obj)->txm.scale, 0, 1))
		return (ft_error("Invalid texture scale [0,1]"));
	if ((*obj)->txm.type == 1 && len > 2 && split[2]
		&& !ft_get_rgb(&(*obj)->txm.sec_color, split[2]))
		return (false);
	if ((*obj)->txm.type == 2 && len > 2 && split[2]
		&& !ft_load_xpm_texture(scene, obj, split[2]))
		return (false);
	return (true);
}

bool	ft_add_texture(t_scene **scene, t_obj_data **obj, char *str)
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
	result = ft_populate_texture(scene, obj, split, len);
	original = split;
	while (*split)
		free(*split++);
	free(original);
	return (result);
}
