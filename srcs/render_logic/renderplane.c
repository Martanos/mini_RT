/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderplane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:17:32 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/04 13:54:22 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "plane.h"

static t_vect calculate_viewport_up(t_vect camera_dir)
{
	t_vect world_up = vect_create(0.0, 1.0, 0.0);
	t_vect right = vect_normalize(vect_cross(camera_dir, world_up));
	return vect_normalize(vect_cross(right, camera_dir));
}
// todo: move to parser
void initmlx(t_master *master)
{
	master->mlx_ptr = mlx_init();
	if (!master->mlx_ptr)
		error_exit("mlx failed to initialize");
	master->win_ptr = mlx_new_window(master->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "miniRT");
	if (!master->win_ptr)
		error_exit("mlx failed to create window");
	master->img.img_ptr = mlx_new_image(master->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!master->img.img_ptr)
		error_exit("mlx failed to create image");
	master->img.pixels_ptr = mlx_get_data_addr(master->img.img_ptr, &master->img.bpp, &master->img.line_len, &master->img.endian);
	if (!master->img.pixels_ptr)
		error_exit("mlx failed to get image address");
}

uint32_t	calculations(int x, int y, t_master *master)
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
	camera_dir = vect_normalize(master->cam_head.norm);
	
	// Calculate viewport dimensions based on FOV
	viewport_height = 2.0 * tan((master->cam_head.fov * M_PI / 180.0) / 2.0);
	viewport_width = viewport_height * aspect_ratio;
	focal_length = 1.0;
	
	// Calculate viewport orientation vectors
	viewport_up = calculate_viewport_up(camera_dir);
	viewport_right = vect_normalize(vect_cross(camera_dir, viewport_up));
	
	// Calculate viewport vectors
	t_vect horizontal = vect_multiply(viewport_right, viewport_width);
	t_vect vertical = vect_multiply(viewport_up, -viewport_height);  // Negative to match screen coordinates
	
	// Calculate viewport center and corner
	t_vect viewport_center = vect_add(master->cam_head.cord, 
		vect_multiply(camera_dir, focal_length));
	t_vect viewport_upper_left = vect_sub(viewport_center, 
		vect_add(vect_divide(horizontal, 2.0), vect_divide(vertical, 2.0)));
	
	// Calculate pixel position
	double u = (double)x / (WINDOW_WIDTH - 1);
	double v = (double)y / (WINDOW_HEIGHT - 1);
	pixel_pos = vect_add(viewport_upper_left,
		vect_add(vect_multiply(horizontal, u), vect_multiply(vertical, v)));
	
	// Setup and normalize ray
	ray.origin = master->cam_head.cord;
	ray.direction = vect_normalize(vect_sub(pixel_pos, ray.origin));
	
	return (ray_color(ray, master));
}

void start_renderloop(t_master *master)
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
			color = calculations(x, y, master);
			my_pixel_put(&master->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(master->mlx_ptr, master->win_ptr, master->img.img_ptr, 0, 0);
	
	mlx_hook(master->win_ptr, 17, 0, close_window, master);
	mlx_key_hook(master->win_ptr, key_hook, master);
	
	mlx_loop(master->mlx_ptr);
}

void	ft_render_scene(t_master *master)
{
	initmlx(master);
	start_renderloop(master);
}
