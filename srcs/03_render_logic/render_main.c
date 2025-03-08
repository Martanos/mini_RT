/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:07:21 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/08 10:51:09 by malee            ###   ########.fr       */
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
			if (color != 0x00000000)
				my_pixel_put(&master->img, pos[0], pos[1], color);
		}
		printf("\033[1A\033[2K");
		printf(YELLOW "Rendering progress: %d%%\n" RESET, (pos[1] * 100)
			/ WINDOW_HEIGHT);
	}
	printf("\033[1A\033[2K");
	printf(GREEN "Rendering complete\n" RESET);
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
