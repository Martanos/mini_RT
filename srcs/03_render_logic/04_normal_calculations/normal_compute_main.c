/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_compute_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:54:19 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 10:02:44 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * Create an orthonormal basis (tangent, bitangent) around a normal vector
 */
static void	ft_create_orthonormal_basis(t_vect normal, t_vect *tangent,
		t_vect *bitangent)
{
	t_vect	temp;

	temp = (t_vect){1, 0, 0};
	if (fabs(ft_vect_dot(normal, temp)) > 0.9)
		temp = (t_vect){0, 1, 0};
	*tangent = ft_vect_norm(ft_vect_cross(normal, temp));
	*bitangent = ft_vect_cross(normal, *tangent);
}

/**
 * Calculate the complete surface normal at the intersection point
 */
void	ft_calculate_surface_normal(t_hit **hit)
{
	if (!(*hit)->tangent.x && !(*hit)->tangent.y && !(*hit)->tangent.z)
		ft_create_orthonormal_basis((*hit)->normal, &(*hit)->tangent,
			&(*hit)->bitangent);
	if ((*hit)->object->bpm.enabled && (*hit)->object->bpm.data)
		ft_apply_bump_mapping(hit);
	(*hit)->normal = ft_vect_norm((*hit)->normal);
	if (!(*hit)->front_face)
		(*hit)->normal = ft_vect_mul_all((*hit)->normal, -1);
}
