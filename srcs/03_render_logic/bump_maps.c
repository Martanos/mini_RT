/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 04:15:29 by malee             #+#    #+#             */
/*   Updated: 2025/03/08 09:29:56 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	get_bump_height(t_bump_map bpm, double u, double v)
{
	int		color;
	double	height;
	int		x;
	int		y;

	v = 1.0 - v;
	x = (int)(u * bpm.width) % bpm.width;
	y = (int)(v * bpm.height) % bpm.height;
	if (x < 0 || y < 0 || x >= bpm.width || y >= bpm.height)
		return (0.0);
	color = bpm.data[y * bpm.width + x];
	if (color == 0x00000000)
		return (0.0);
	height = (double)((color & 0xFF) + ((color >> 8) & 0xFF)
			+ ((color >> 16) & 0xFF)) / (3.0 * 255.0);
	return (height);
}

static void	calculate_bump_gradient(t_bump_map bpm, double u, double v,
		double grad[2])
{
	double	step_u;
	double	step_v;
	double	h;
	double	h_u;
	double	h_v;

	step_u = 1.0 / bpm.width;
	step_v = 1.0 / bpm.height;
	h = get_bump_height(bpm, u, v);
	h_u = get_bump_height(bpm, u + step_u, v);
	h_v = get_bump_height(bpm, u, v + step_v);
	if (h == 0.0 || h_u == 0.0 || h_v == 0.0)
		return ;
	grad[0] = (h_u - h) * BUMP_MAP_STRENGTH * bpm.width;
	grad[1] = (h_v - h) * BUMP_MAP_STRENGTH * bpm.height;
}

static void	create_tangent_space(t_vect normal, t_vect *tangent,
		t_vect *bitangent)
{
	t_vect	up;

	up = ft_vect_create(0, 1, 0);
	if (fabs(ft_vect_dot(normal, up)) > 0.99)
		up = ft_vect_create(1, 0, 0);
	*tangent = ft_vect_norm(ft_vect_cross(up, normal));
	*bitangent = ft_vect_norm(ft_vect_cross(normal, *tangent));
}

void	apply_bump_mapping(t_bump_map bpm, t_hit_record *hit, double u,
		double v)
{
	double	grad[2];
	t_vect	perturbed;
	t_vect	tangent;
	t_vect	bitangent;

	if (!bpm.enabled || !bpm.data)
		return ;
	grad[0] = 0;
	grad[1] = 0;
	calculate_bump_gradient(bpm, u, v, grad);
	if (grad[0] == 0.0 && grad[1] == 0.0)
		return ;
	if (hit->tangent.x == 0 && hit->tangent.y == 0 && hit->tangent.z == 0)
		create_tangent_space(hit->normal, &tangent, &bitangent);
	else
	{
		tangent = hit->tangent;
		bitangent = hit->bitangent;
	}
	perturbed = hit->normal;
	perturbed = ft_vect_sub(perturbed, ft_vect_mul_all(tangent, grad[0]));
	perturbed = ft_vect_sub(perturbed, ft_vect_mul_all(bitangent, grad[1]));
	hit->normal = ft_vect_norm(perturbed);
}
