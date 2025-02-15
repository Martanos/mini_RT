/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:52:02 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/15 19:10:59 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

uint32_t    checkerboard(t_vect point, t_texture texture)
{
	int check_x = (int)floor(point.x * texture.scale) % 2;
	int check_z = (int)floor(point.z * texture.scale) % 2;
	if ((check_x + check_z) % 2 == 0)
		return (texture.pri_color);
	return (texture.sec_color);
}