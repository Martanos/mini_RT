/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:13:52 by malee             #+#    #+#             */
/*   Updated: 2025/03/22 14:35:20 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_free_node(void *node, t_obj_type type, t_master *master)
{
	t_obj_pro	*properties;

	if (!node)
		return ;
	properties = NULL;
	if (type != TYPE_LIGHT)
	{
		if (type == TYPE_SPHERE)
			properties = &((t_sphere *)node)->pro;
		else if (type == TYPE_PLANE)
			properties = &((t_plane *)node)->pro;
		else if (type == TYPE_CYLINDER)
			properties = &((t_cylinder *)node)->pro;
		else if (type == TYPE_CONE)
			properties = &((t_cone *)node)->pro;
	}
	if (properties && properties->txm.img)
		mlx_destroy_image(master->mlx_ptr, properties->txm.img);
	if (properties && properties->bpm.img)
		mlx_destroy_image(master->mlx_ptr, properties->bpm.img);
	free(node);
}

void	ft_free_list(void *head, t_obj_type type, t_master *master)
{
	void	*current;
	void	*next;

	if (!head)
		return ;
	current = head;
	while (current)
	{
		if (type == TYPE_LIGHT)
			next = ((t_light *)current)->next;
		if (type == TYPE_SPHERE)
			next = ((t_sphere *)current)->next;
		if (type == TYPE_PLANE)
			next = ((t_plane *)current)->next;
		if (type == TYPE_CYLINDER)
			next = ((t_cylinder *)current)->next;
		if (type == TYPE_CONE)
			next = ((t_cone *)current)->next;
		ft_free_node(current, type, master);
		current = next;
		next = NULL;
	}
}

void	ft_free_img(t_master *master)
{
	if (!master)
		return ;
	if (master->mlx_ptr && master->win_ptr)
	{
		mlx_destroy_window(master->mlx_ptr, master->win_ptr);
		master->win_ptr = NULL;
	}
	if (master->mlx_ptr && master->img.img_ptr)
	{
		mlx_destroy_image(master->mlx_ptr, master->img.img_ptr);
		master->img.img_ptr = NULL;
	}
	if (master->mlx_ptr)
	{
		mlx_destroy_display(master->mlx_ptr);
		free(master->mlx_ptr);
		master->mlx_ptr = NULL;
	}
}

void	ft_free_master(t_master *master)
{
	if (!master)
		return ;
	ft_free_list(master->light_head, TYPE_LIGHT, master);
	ft_free_list(master->sphere_head, TYPE_SPHERE, master);
	ft_free_list(master->plane_head, TYPE_PLANE, master);
	ft_free_list(master->cylinder_head, TYPE_CYLINDER, master);
	ft_free_list(master->cone_head, TYPE_CONE, master);
	ft_free_img(master);
	free(master);
}
