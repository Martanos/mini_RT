/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:46:05 by malee             #+#    #+#             */
/*   Updated: 2025/02/06 22:34:04 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// TODO: Potential issue with freeing the image may need mlx_destroy_image
void	ft_free_node(void *node, t_obj_type type)
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
	if (properties)
	{
		free(properties->txm.img);
		if (properties->bpm.map)
			free(properties->bpm.map);
	}
	free(node);
}

void	ft_free_list(void *head, t_obj_type type)
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
		ft_free_node(current, type);
		current = next;
		next = NULL;
	}
}
