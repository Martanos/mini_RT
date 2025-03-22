/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:45:49 by malee             #+#    #+#             */
/*   Updated: 2025/03/22 15:03:22 by malee            ###   ########.fr       */
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

static bool	ft_populate_light(t_light **light, t_p_node **cur)
{
	if (!ft_next(cur, "Light has no coordinates"))
		return (false);
	(*light)->cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*light)->cord, -INFINITY, INFINITY,
			"Light coordinates are not a valid vector [-INFINITY, INFINITY]")
		|| !ft_next(cur, "Light has no ratio"))
		return (false);
	(*light)->ratio = ft_atod((*cur)->str);
	if (!ft_inrange((*light)->ratio, 0, 1))
		return (ft_error("Light ratio is out of range [0,1]"));
	if (!ft_next(cur, "Light has no color"))
		return (false);
	if (!ft_get_rgb(&(*light)->color, (*cur)->str))
		return (false);
	(*cur) = (*cur)->next;
	if ((*cur) && (*cur)->str != NULL && (*cur)->str[0] != '\n')
		return (ft_error("Light has extra data"));
	return (true);
}

bool	ft_create_light(t_master **master, t_p_node **cur)
{
	t_light	*light;

	light = (t_light *)ft_calloc(1, sizeof(t_light));
	if (!light)
		return (false);
	if (!ft_populate_light(&light, cur))
		return (ft_free_node(light, TYPE_LIGHT, *master), false);
	ft_add_light(master, light);
	return (true);
}
