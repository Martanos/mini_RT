/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:07:21 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/08 09:55:52 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	start_renderloop(t_master *master)
{
	uint32_t	color;
	int			pos[2];

	pos[1] = -1;
	while (++pos[1] < WINDOW_HEIGHT)
	{
		pos[0] = -1;
		while (++pos[0] < WINDOW_WIDTH)
		{
			color = calculations(pos, master);
			my_pixel_put(&master->img, pos[0], pos[1], color);
		}
	}
	mlx_put_image_to_window(master->mlx_ptr, master->win_ptr,
		master->img.img_ptr, 0, 0);
	mlx_hook(master->win_ptr, 17, 0, close_window, master);
	mlx_key_hook(master->win_ptr, key_hook, master);
	mlx_loop(master->mlx_ptr);
}

void	ft_render_scene(t_master *master)
{
	start_renderloop(master);
}
