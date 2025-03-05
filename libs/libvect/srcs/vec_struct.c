/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 01:32:16 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 10:12:04 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"

t_vect	ft_vect_create(double x, double y, double z)
{
	t_vect	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vect	ft_rgb_to_vect(uint32_t rgb)
{
	t_vect	v;

	v.x = (rgb >> 16) & 0xFF;
	v.y = (rgb >> 8) & 0xFF;
	v.z = rgb & 0xFF;
	return (v);
}
