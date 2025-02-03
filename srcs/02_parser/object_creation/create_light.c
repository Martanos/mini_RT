/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:45:49 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 20:38:37 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_add_light(t_master **master, t_light *light)
{
	t_light	*temp;

	if ((*master)->light_head == NULL)
		(*master)->light_head = light;
	else
	{
		temp = (*master)->light_head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = light;
	}
}

bool	ft_create_light(t_master **master, t_p_node **cur)
{
	t_light	*light;

	light = (t_light *)ft_calloc(1, sizeof(t_light));
	if (!light)
		return (false);
	(*cur) = (*cur)->next;
	light->cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector(light->cord, -INFINITY, INFINITY))
		return (free(light),
			ft_format_error("Light coordinates are not a valid vector"));
	(*cur) = (*cur)->next;
	light->ratio = ft_atod((*cur)->str);
	if (!ft_inrange(light->ratio, 0, 1))
		return (free(light),
			ft_format_error("Light ratio is out of range [0,1]"));
	(*cur) = (*cur)->next;
	light->color = ft_get_rgb((*cur)->str);
	if (light->color < 0 || light->color > 0xFFFFFF)
		return (free(light),
			ft_format_error("Light color is out of range [0,255]"));
	(*cur) = (*cur)->next;
	if (*cur && !ft_check_extra(&light, cur))
		return (free(light), false);
	ft_add_light(master, light);
	return (true);
}
