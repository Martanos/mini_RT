/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_compute_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 08:49:03 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 09:57:26 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_colour_compute_main(t_scene **scene)
{
	ft_get_base_colour(&(*scene)->z_buffer);
	ft_calculate_surface_normal((*scene)->z_buffer);
}
