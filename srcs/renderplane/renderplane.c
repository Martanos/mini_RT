/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderplane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:17:32 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/07 12:58:16 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "plane.h"

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
// }

t_vect calculate_viewport_up(t_vect camera_dir)
{
	t_vect world_up = vect_create(0.0, 1.0, 0.0);
	t_vect right = vect_normalize(vect_cross(camera_dir, world_up));
	return vect_normalize(vect_cross(right, camera_dir));
}

uint32_t	calculations(int x, int y, t_data *mlx_data)
{
	double	aspect_ratio;
	t_vect	pixel_pos;
	t_ray	ray;
	t_vect	camera_dir;
	t_vect	viewport_up;
	t_vect	viewport_right;
	double	viewport_height;
	double	viewport_width;
	double	focal_length;

	aspect_ratio = (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT;
	camera_dir = vect_normalize(mlx_data->instruction_set->camera_dir);
	
	// Calculate viewport dimensions based on FOV
	viewport_height = 2.0 * tan((mlx_data->instruction_set->camera_view_fov * M_PI / 180.0) / 2.0);
	viewport_width = viewport_height * aspect_ratio;
	focal_length = 1.0;
	
	// Calculate viewport orientation vectors
	viewport_up = calculate_viewport_up(camera_dir);
	viewport_right = vect_normalize(vect_cross(camera_dir, viewport_up));
	
	// Calculate viewport vectors
	t_vect horizontal = vect_multiply(viewport_right, viewport_width);
	t_vect vertical = vect_multiply(viewport_up, -viewport_height);  // Negative to match screen coordinates
	
	// Calculate viewport center and corner
	t_vect viewport_center = vect_add(mlx_data->instruction_set->camera_pos, 
		vect_multiply(camera_dir, focal_length));
	t_vect viewport_upper_left = vect_sub(viewport_center, 
		vect_add(vect_divide(horizontal, 2.0), vect_divide(vertical, 2.0)));
	
	// Calculate pixel position
	double u = (double)x / (WINDOW_WIDTH - 1);
	double v = (double)y / (WINDOW_HEIGHT - 1);
	pixel_pos = vect_add(viewport_upper_left,
		vect_add(vect_multiply(horizontal, u), vect_multiply(vertical, v)));
	
	// Setup and normalize ray
	ray.origin = mlx_data->instruction_set->camera_pos;
	ray.direction = vect_normalize(vect_sub(pixel_pos, ray.origin));
	
	return (ray_color(ray, mlx_data));
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
