/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderplane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:17:32 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/05 16:15:45 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "plane.h"

/*
to render a plane successfully

data values required:
camera vectors
camera view vectors
camera fov

plane struct; */

void initmlx(t_data *mlx_data, t_instruction_set *instruction_set)
{
	mlx_data->mlx_ptr = mlx_init();
	if (!mlx_data->mlx_ptr)
		error_exit("mlx failed to initialize");
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT");
	if (!mlx_data->win_ptr)
		error_exit("mlx failed to create window");
	mlx_data->img.img_ptr = mlx_new_image(mlx_data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx_data->img.img_ptr)
		error_exit("mlx failed to create image");
	mlx_data->img.pixels_ptr = mlx_get_data_addr(mlx_data->img.img_ptr, &mlx_data->img.bpp, &mlx_data->img.line_len, &mlx_data->img.endian);
	if (!mlx_data->img.pixels_ptr)
		error_exit("mlx failed to get image address");
	mlx_data->instruction_set = instruction_set;
	
}

void start_renderloop(t_data *mlx_data)
{
	int x;
	int y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			my_pixel_put(&mlx_data->img, x, y, BLUE);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx_data->mlx_ptr, mlx_data->win_ptr, mlx_data->img.img_ptr, 0, 0);
	
	mlx_hook(mlx_data->win_ptr, 17, 0, close_window, mlx_data);
	mlx_key_hook(mlx_data->win_ptr, key_hook, mlx_data);
	
	mlx_loop(mlx_data->mlx_ptr);
}
void	ft_render_plane(t_instruction_set *instruction_set)
{
	t_data mlx_data;
	

	initmlx(&mlx_data, instruction_set);
	start_renderloop(&mlx_data);
}