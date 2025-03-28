/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sean <sean@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:59:59 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/04 16:10:14 by sean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

int	close_window(void *param)
{
	t_master	*master;

	master = (t_master *)param;
	ft_free_master(master);
	exit(0);
	return (0);
}

// Handle keypress event
int	key_hook(int keycode, void *param)
{
	t_master	*master;

	master = (t_master *)param;
	if (keycode == 65307)
	{
		ft_free_master(master);
		exit(0);
	}
	return (0);
}
