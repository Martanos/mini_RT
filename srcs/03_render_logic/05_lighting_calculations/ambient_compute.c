/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_compute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:01:24 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 17:09:07 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_add_ambient_to_base(t_scene **scene, t_z_buffer **z_buffer)
{
	if ((*z_buffer)->cam_hit.object->txm.type == SOLID_COLOR)
	{
	}
	else if ((*z_buffer)->cam_hit.object->txm.type == CHECKERED)
		(*z_buffer)->cam_hit.calc_color = ft_vect_add((*z_buffer)->cam_hit.calc_color,
				ft_rgb_to_vect((*scene)->amb_data.rgb));
	else if ((*z_buffer)->cam_hit.object->txm.type == CUSTOM)
		(*z_buffer)->cam_hit.calc_color = ft_vect_add((*z_buffer)->cam_hit.calc_color,
				ft_rgb_to_vect((*scene)->amb_data.rgb));
}
