/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_calcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:05:02 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 12:03:00 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_init_local_cords(t_obj_data **obj)
{
	t_vect	temp;

	(*obj)->norm_dir = ft_vect_norm((*obj)->dir);
	if (fabs((*obj)->dir.x) < 0.7)
		temp = ft_vect_create(1, 0, 0);
	else
		temp = ft_vect_create(0, 1, 0);
	(*obj)->tangent = ft_vect_norm(ft_vect_cross(temp, (*obj)->norm_dir));
	(*obj)->bitangent = ft_vect_norm(ft_vect_cross((*obj)->norm_dir,
				(*obj)->tangent));
}

void	ft_setup_obj_calcs(t_scene **scene)
{
	t_obj_data	*obj;

	obj = (*scene)->obj_head;
	while (obj)
	{
		ft_init_local_cords(&obj);
		if (obj->type == SPHERE)
			ft_setup_sphere(&obj);
		else if (obj->type == PLANE)
			ft_setup_plane(&obj);
		else if (obj->type == CYLINDER)
			ft_setup_cylinder(&obj);
		else if (obj->type == CONE)
			ft_setup_cone(&obj);
		obj = obj->next;
	}
}
