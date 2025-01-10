/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:52:08 by malee             #+#    #+#             */
/*   Updated: 2025/01/10 21:45:03 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_free_light(t_light *light)
{
	t_light	*temp;

	temp = light;
	while (light)
	{
		temp = light;
		light = light->next;
		free(temp);
		temp = NULL;
	}
	light = NULL;
}

void	ft_free_plane(t_plane *plane)
{
	t_plane	*temp;

	temp = plane;
	while (plane)
	{
		temp = plane;
		plane = plane->next;
		free(temp);
		temp = NULL;
	}
}

void	ft_free_sphere(t_sphere *sphere)
{
	t_sphere	*temp;

	temp = sphere;
	while (sphere)
	{
		temp = sphere;
		sphere = sphere->next;
		free(temp);
		temp = NULL;
	}
}

void	ft_free_cylinder(t_cylinder *cylinder)
{
	t_cylinder	*temp;

	temp = cylinder;
	while (cylinder)
	{
		temp = cylinder;
		cylinder = cylinder->next;
		free(temp);
		temp = NULL;
	}
}

void	ft_free_master(t_master *master)
{
	free(master->amb_head);
	ft_free_cam(master->cam_head);
	ft_free_light(master->light_head);
	ft_free_plane(master->plane_head);
	ft_free_cylinder(master->cylinder_head);
	ft_free_sphere(master->sphere_head);
	free(master);
	master = NULL;
}
