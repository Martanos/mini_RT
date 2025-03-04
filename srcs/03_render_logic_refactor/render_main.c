/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:07:29 by malee             #+#    #+#             */
/*   Updated: 2025/03/04 15:50:24 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_calculate_pixel(t_scene **scene, int x, int y)
{
	(*scene)->z_buffer[0].u;
	(*scene) return (true);
}

bool	ft_render_main(t_scene **scene)
{
	int	x;
	int	y;

	y = 0;
	if (!ft_object_prep(scene))
		return (false);
	while (y < (*scene)->cam_data.win_height)
	{
		x = 0;
		while (x < (*scene)->cam_data.win_width)
		{
			if (ft_calculate_pixel(scene, x, y))
				ft_pixel_put(&(*scene)->img, x, y,
					(*scene)->z_buffer[0].pixel_color);
			x++;
			ft_clear_buffers(scene);
		}
		y++;
	}
	return (true);
}
