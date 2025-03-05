/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_compute_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:49:03 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 09:51:27 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_colour_compute_main(t_scene **scene)
{
	ft_get_base_colour(&(*scene)->z_buffer);
	if ((*scene)->z_buffer->object->bpm.enabled
		&& (*scene)->z_buffer->object->bpm.data)
		ft_apply_bump_mapping((*scene)->z_buffer);
}
