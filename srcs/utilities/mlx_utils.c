/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:59:59 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/06 14:11:35 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static int	close_window(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	ft_free_scene(scene);
	exit(0);
	return (0);
}

// Handle keypress event
static int	key_hook(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keycode == 65307)
	{
		ft_free_scene(scene);
		exit(0);
	}
	return (0);
}

void	keyhook_wrapper(t_scene **scene)
{
	mlx_hook((*scene)->win_ptr, 17, 0, close_window, *scene);
	mlx_key_hook((*scene)->win_ptr, key_hook, *scene);
}
