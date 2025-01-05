/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderplane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:17:32 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/05 14:32:41 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"
#include "plane.h"

/*
to render a plane successfully

data values required:
camera vectors
camera view vectors
camera fov

plane struct; */

void error_exit(char *error_message)
{
	printf("Error\n%s\n", error_message);
	exit(1);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main(void)
{
	t_instruction_set data;
	t_data mlx_data;
	t_plane_obj plane;

	// set camera vectors
	data.camera_view_x = 0;
	data.camera_view_y = 0;
	data.camera_view_z = 0;
	data.camera_view_normal_x = 0;
	data.camera_view_normal_y = 0;
	data.camera_view_normal_z = 0;
	data.camera_view_fov = 0;

	// set plane vectors
	plane.plane_x = 0;
	plane.plane_y = 0;
	plane.plane_z = 0;
	plane.plane_normal_x = 0;
	plane.plane_normal_y = 0;
	plane.plane_normal_z = 0;

	initmlx(&mlx_data);

	return (0);
}

void initmlx(t_data *mlx_data)
{
	mlx_data->mlx_ptr = mlx_init();
	if (!mlx_data->mlx_ptr)
		error_exit("mlx failed to initialize");
	
}