/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderplane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:17:32 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/05 18:35:55 by seayeo           ###   ########.fr       */
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
uint32_t	ray_color(t_ray ray)
{
	// if ray intersects with object
	// return object color
	// else
	// return background color
	t_vect unit_direction = vect_normalize(ray.direction);
	double t = 0.5 * (unit_direction.y + 1.0);
	return ((1.0 - t) * WHITE + t * BLUE);	
}

// void	trace_ray(t_ray ray, t_instruction_set *instruction_set)
// {
// 	t_plane_obj	*plane_obj;
// 	t_sphere_obj	*sphere_obj;
// 	t_cylinder_obj	*cylinder_obj;
// 	t_light_obj		*light_obj;
	
// 	plane_obj = *(instruction_set->plane_obj_list);
// 	sphere_obj = *(instruction_set->sphere_obj_list);
// 	cylinder_obj = *(instruction_set->cylinder_obj_list);
// 	light_obj = *(instruction_set->light_obj_list);
	
// 	// check if ray intersects with plane
// 	// check if ray intersects with sphere
// 	// check if ray intersects with cylinder
// 	// check if ray intersects with triangle
// 	// check if ray intersects with square
// 	// check if ray intersects with cone
// }

uint32_t	calculations(int x, int y, t_data *mlx_data)
{
	double	aspect_ratio;
	t_vect	pixel_pos;
	t_ray	ray;

	aspect_ratio = WINDOW_WIDTH / WINDOW_HEIGHT;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * aspect_ratio;
	double focal_length = 1.0;
	
	// x and y axis vectors for the viewport
	t_vect horizontal;
	horizontal = vect_create(viewport_width, 0.0, 0.0);
	t_vect vertical;
	vertical = vect_create(0.0, viewport_height, 0.0);
	
	// unit vectors for moving between pixels
	t_vect pixel_unit_vector_horizontal;
	pixel_unit_vector_horizontal = vect_divide(horizontal, WINDOW_WIDTH);
	t_vect pixel_unit_vector_vertical;
	pixel_unit_vector_vertical = vect_divide(vertical, WINDOW_HEIGHT);
	

	// first pixel upper left corner
	t_vect viewport_top_left;
	viewport_top_left = vect_sub(mlx_data->instruction_set->camera_pos, vect_create(0, 0, focal_length));
	viewport_top_left = vect_sub(viewport_top_left, vect_divide(horizontal, 2));
	viewport_top_left = vect_sub(viewport_top_left, vect_divide(vertical, 2));
	t_vect first_pixel;
	first_pixel = vect_add(viewport_top_left, vect_divide(vect_add(horizontal, vertical), 2));
	
	pixel_pos = vect_add(vect_multiply(pixel_unit_vector_horizontal, x), vect_multiply(pixel_unit_vector_vertical, y));
	pixel_pos = vect_add(first_pixel, pixel_pos);
	// current_pixel = vect_add(first_pixel, vect_add(pixel_unit_vector_horizontal * x, pixel_unit_vector_vertical * y));
	
	ray.origin = mlx_data->instruction_set->camera_pos;
	ray.direction = vect_normalize(vect_sub(pixel_pos, mlx_data->instruction_set->camera_pos));
	

	// trace_ray(ray, mlx_data->instruction_set);
	uint32_t color = ray_color(ray);
	return (color);
}


void start_renderloop(t_data *mlx_data)
{
	int x;
	int y;
	uint32_t color;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			color = calculations(x, y, mlx_data);
			my_pixel_put(&mlx_data->img, x, y, color);
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