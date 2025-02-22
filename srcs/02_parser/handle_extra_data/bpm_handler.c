/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bpm_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:19:32 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 22:40:09 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_add_bump_map(t_scene **scene, t_obj_data **obj, char *str)
{
	ssize_t	len;
	int		fd;

	if (!str)
		return (ft_error("No bpm texture data specified"));
	(*obj)->bpm.enabled = true;
	len = ft_strlen(str);
	if (len < 4 || str[len - 1] != 'm' || str[len - 2] != 'p' || str[len
		- 3] != 'x' || str[len - 4] != '.')
		return (ft_error("Invalid bpm file extension expected: .xpm"), false);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_error("Failed to access bpm texture file"), false);
	close(fd);
	(*obj)->bpm.img = mlx_xpm_file_to_image((*scene)->mlx_ptr, str,
			&(*obj)->bpm.width, &(*obj)->bpm.height);
	if (!(*obj)->bpm.img)
		return (ft_error("Failed to load bpm texture from file"), false);
	(*obj)->bpm.data = (int *)mlx_get_data_addr((*obj)->bpm.img,
			&(*obj)->bpm.bpp, &(*obj)->bpm.line_len, &(*obj)->bpm.endian);
	if (!(*obj)->bpm.data)
		return (ft_error("Failed to get bpm texture data"), false);
	return (true);
}
