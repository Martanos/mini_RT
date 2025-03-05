/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_map_compute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:16:56 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 09:49:06 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * Get image coordinates from UV coordinates with proper wrapping
 */
static void	ft_get_image_coordinates(t_hit *hit, t_obj_data *obj, int *img_x,
		int *img_y)
{
	*img_x = (int)(hit->u * obj->bpm.width) % obj->bpm.width;
	*img_y = (int)(hit->v * obj->bpm.height) % obj->bpm.height;
	if (*img_x < 0)
		*img_x += obj->bpm.width;
	if (*img_y < 0)
		*img_y += obj->bpm.height;
}

/*
 * Perturb normal based on height gradients and tangent/bitangent vectors
 */
static t_vect	ft_perturb_normal(t_hit *hit, double dx, double dy,
		double bump_strength)
{
	t_vect	perturbed;

	perturbed = hit->normal;
	perturbed = ft_vect_add(perturbed, ft_vect_mul_all(hit->tangent, -dx
				* bump_strength));
	perturbed = ft_vect_add(perturbed, ft_vect_mul_all(hit->bitangent, -dy
				* bump_strength));
	return (ft_vect_norm(perturbed));
}

/*
 * Main bump mapping function that uses the helper functions
 */
void	ft_apply_bump_mapping(t_hit *hit)
{
	int		img_x;
	int		img_y;
	double	height_dx;
	double	height_dy;
	double	height;

	img_x = 0;
	img_y = 0;
	if (!hit->object->bpm.enabled || hit->object->bpm.data == NULL)
		return ;
	ft_get_image_coordinates(hit, hit->object, &img_x, &img_y);
	height = (hit->object->bpm.data[img_y * hit->object->bpm.width
			+ img_x] & 0xFF) / 255.0;
	height_dx = (hit->object->bpm.data[img_y * hit->object->bpm.width + ((img_x
					+ 1) % hit->object->bpm.width)] & 0xFF) / 255.0;
	height_dy = (hit->object->bpm.data[((img_y + 1) % hit->object->bpm.height)
			* hit->object->bpm.width + img_x] & 0xFF) / 255.0;
	hit->normal = ft_perturb_normal(hit, height_dx - height, height_dy - height,
			0.05);
}
