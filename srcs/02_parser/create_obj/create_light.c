/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:45:49 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 22:47:54 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_populate_light(t_obj_data **obj, t_p_node **cur)
{
	if (!ft_next(cur, "Light has no coordinates"))
		return (false);
	(*obj)->cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*obj)->cord, -INFINITY, INFINITY,
			"Light coordinates are not a valid vector [-INFINITY, INFINITY]")
		|| !ft_next(cur, "Light has no ratio"))
		return (false);
	(*obj)->props.light.ratio = ft_atod((*cur)->str);
	if (!ft_inrange((*obj)->props.light.ratio, 0, 1))
		return (ft_error("Light ratio is out of range [0,1]"));
	if (!ft_next(cur, "Light has no color"))
		return (false);
	if (!ft_get_rgb(&(*obj)->txm.pri_color, (*cur)->str))
		return (false);
	(*cur) = (*cur)->next;
	if ((*cur) && (*cur)->str != NULL && (*cur)->str[0] != '\n')
		return (ft_error("Light has extra data"));
	return (true);
}

bool	ft_create_light(t_scene **scene, t_p_node **cur, t_obj_type type)
{
	t_obj_data	*obj;

	obj = (t_obj_data *)ft_calloc(1, sizeof(t_obj_data));
	if (!obj)
		return (false);
	obj->type = type;
	if (!ft_populate_light(obj, cur))
		return (free(obj), false);
	ft_add_obj(scene, obj);
	printf(GREEN "Light created successfully\n" RESET);
	(*scene)->light_set = true;
	return (true);
}
