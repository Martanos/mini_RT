/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sean <sean@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:24:12 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/04 13:53:45 by sean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	checkerboard(double u, double v, t_texture txm, uint32_t *color)
{
	int	u_check;
	int	v_check;

	u_check = ((int)floor(u * txm.scale * 8)) % 2;
	v_check = ((int)floor(v * txm.scale * 8)) % 2;
	if ((u_check && v_check) || (!u_check && !v_check))
		*color = txm.pri_color;
	else
		*color = txm.sec_color;
}
