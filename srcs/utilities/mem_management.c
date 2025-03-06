/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:13:52 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 13:33:08 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_free_node(t_obj_data *node, t_scene *scene)
{
	if (!node)
		return ;
	if (node->txm.img && node->txm.data)
		mlx_destroy_image(scene->mlx_ptr, node->txm.img);
	if (node->bpm.img)
		mlx_destroy_image(scene->mlx_ptr, node->bpm.img);
	free(node);
}

void	ft_free_obj_list(t_obj_data *head, t_scene *scene)
{
	t_obj_data	*current;
	t_obj_data	*next;

	if (!head)
		return ;
	current = head;
	while (current)
	{
		next = current->next;
		ft_free_node(current, scene);
		current = next;
		next = NULL;
	}
}

void	ft_free_light_list(t_light *head)
{
	t_light	*current;
	t_light	*next;

	if (!head)
		return ;
	current = head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
		next = NULL;
	}
}

void	ft_free_img(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->mlx_ptr && scene->win_ptr)
	{
		mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
		scene->win_ptr = NULL;
	}
	if (scene->mlx_ptr && scene->img.img_ptr)
	{
		mlx_destroy_image(scene->mlx_ptr, scene->img.img_ptr);
		scene->img.img_ptr = NULL;
	}
	if (scene->mlx_ptr)
	{
		mlx_destroy_display(scene->mlx_ptr);
		free(scene->mlx_ptr);
		scene->mlx_ptr = NULL;
	}
}

void	ft_free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	ft_free_light_list(scene->light_data);
	ft_free_obj_list(scene->obj_head, scene);
	ft_free_img(scene);
	free(scene);
}
