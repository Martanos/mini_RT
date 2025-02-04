/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderplane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:17:32 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/04 16:23:28 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "libvect.h"

static t_vect calculate_viewport_up(t_vect camera_dir)
{
	t_vect world_up = ft_vect_create(0.0, 1.0, 0.0);
	t_vect right = ft_vect_norm(ft_vect_cross(camera_dir, world_up));
	return ft_vect_norm(ft_vect_cross(right, camera_dir));
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
	camera_dir = ft_vect_norm(master->cam_head.norm);
	
	// Calculate viewport dimensions based on FOV
	viewport_height = 2.0 * tan((master->cam_head.fov * M_PI / 180.0) / 2.0);
	viewport_width = viewport_height * aspect_ratio;
	focal_length = 1.0;
	
	// Calculate viewport orientation vectors
	viewport_up = calculate_viewport_up(camera_dir);
	viewport_right = ft_vect_norm(ft_vect_cross(camera_dir, viewport_up));
	
	// Calculate viewport vectors
	t_vect horizontal = ft_vect_mul_all(viewport_right, viewport_width);
	t_vect vertical = ft_vect_mul_all(viewport_up, -viewport_height);  // Negative to match screen coordinates
	
	// Calculate viewport center and corner
	t_vect viewport_center = ft_vect_add(master->cam_head.cord, 
		ft_vect_mul_all(camera_dir, focal_length));
	t_vect viewport_upper_left = ft_vect_sub(viewport_center, 
		ft_vect_add(ft_vect_div_all(horizontal, 2.0), ft_vect_div_all(vertical, 2.0)));
	
	// Calculate pixel position
	double u = (double)x / (WINDOW_WIDTH - 1);
	double v = (double)y / (WINDOW_HEIGHT - 1);
	pixel_pos = ft_vect_add(viewport_upper_left,
		ft_vect_add(ft_vect_mul_all(horizontal, u), ft_vect_mul_all(vertical, v)));
	
	// Setup and normalize ray
	ray.origin = master->cam_head.cord;
	ray.direction = ft_vect_norm(ft_vect_sub(pixel_pos, ray.origin));
	
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
