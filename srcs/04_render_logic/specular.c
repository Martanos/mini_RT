/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:20:19 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/07 15:34:24 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_vect	calc_reflected_ray(t_vect incident, t_vect normal)
{
	t_vect	reflect;
	double	dot;

	dot = ft_vect_dot(incident, normal);
	reflect = ft_vect_sub(incident, ft_vect_mul_all(normal, 2 * dot));
	return (reflect);
}

uint32_t	calc_specular()

