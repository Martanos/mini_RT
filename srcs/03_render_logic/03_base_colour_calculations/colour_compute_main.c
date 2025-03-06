/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_compute_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:49:03 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 16:54:43 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_colour_compute(t_scene **scene, t_z_buffer **z_buffer)
{
	ft_get_base_colour(&(*z_buffer)->cam_hit);
	ft_calculate_surface_normal(&(*z_buffer)->cam_hit);
	ft_calculate_lighting(scene, &(*z_buffer)->cam_ray, &(*z_buffer)->cam_hit);
}
