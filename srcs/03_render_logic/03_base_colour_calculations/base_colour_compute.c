/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_colour_compute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:02:50 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 17:05:17 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_get_custom_colour(t_hit **hit)
{
	int	x;
	int	y;
	int	color;

	if ((*hit)->object->txm.data)
	{
		x = (int)((*hit)->u * (*hit)->object->txm.width);
		y = (int)((*hit)->v * (*hit)->object->txm.height);
		color = (*hit)->object->txm.data[y * (*hit)->object->txm.width + x];
		(*hit)->pixel_color = color;
	}
}

static void	ft_get_checker_colour(t_hit **hit)
{
	int	u_check;
	int	v_check;

	u_check = ((int)floor((*hit)->u * (*hit)->object->txm.scale * 8)) % 2;
	v_check = ((int)floor((*hit)->v * (*hit)->object->txm.scale * 8)) % 2;
	if ((u_check && v_check) || (!u_check && !v_check))
		(*hit)->pixel_color = (*hit)->object->txm.pri_color;
	else
		(*hit)->pixel_color = (*hit)->object->txm.sec_color;
}

void	ft_get_base_colour(t_hit **hit)
{
	if ((*hit)->object->txm.type == SOLID_COLOR)
		(*hit)->calc_color = ft_int_to_rgb(*hit);
	else if ((*hit)->object->txm.type == CHECKERED)
		ft_get_checker_colour(hit);
	else if ((*hit)->object->txm.type == CUSTOM)
		ft_get_custom_colour(hit);
}
