/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sean <sean@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:07:21 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/04 13:44:04 by sean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	start_renderloop(t_master *master)
{
	int			x;
	int			y;
	uint32_t	color;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			color = calculations(x, y, master);
			my_pixel_put(&master->img, x, y, color);
			x++;
		}
		y++;
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
