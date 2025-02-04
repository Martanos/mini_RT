/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:59:59 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/05 15:55:29 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void error_exit(char *error_message)
{
	printf("Error\n%s\n", error_message);
	exit(1);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

int close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

// Handle keypress event
int key_hook(int keycode, void *param)
{
	(void)param;
	if (keycode == 65307) // ESC key
		exit(0);
	return (0);
}
