/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:07:29 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 21:11:27 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_ambient	*ft_init_ambient(t_master *master)
{
	t_ambient	*amb;

	amb = (t_ambient *)ft_calloc(1, sizeof(t_ambient));
	if (!amb)
		return (NULL);
	amb->ratio = master->amb_head.ratio;
	amb->color = master->amb_head.rgb;
	return (amb);
}

t_camera	*ft_init_camera(t_master *master)
{
	t_vect		world_up;
	t_camera	*cam;

	cam = (t_camera *)ft_calloc(1, sizeof(t_camera));
	if (!cam)
		return (NULL);
	cam->fov = master->cam_head.fov * (M_PI / 180);
	cam->pos = master->cam_head.cord;
	cam->dir = ft_vect_norm(master->cam_head.norm);
	world_up = ft_vect_create(0, 1, 0);
	cam->right = ft_vect_norm(ft_vect_cross(cam->up, world_up));
	cam->up = ft_vect_norm(ft_vect_cross(cam->dir, cam->right));
	return (cam);
}

t_scene	*ft_init_scene(t_master *master)
{
	t_scene	*scene;

	scene = (t_scene *)ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (NULL);
	scene->master = master;
	scene->aspect_ratio = (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT;
	scene->amb = ft_init_ambient(master);
	if (!scene->amb)
		return (NULL);
	scene->cam = ft_init_camera(master);
	if (!scene->cam)
		return (NULL);
	scene->obj = ft_init_objects(master);
	if (!scene->obj)
		return (NULL);
	return (scene);
}

bool	ft_render_main(t_master *master)
{
	t_scene	*scene;

	scene = ft_init_scene(master);
	if (!scene)
		return (false);
	return (true);
}
