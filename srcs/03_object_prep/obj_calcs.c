/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_calcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:22:39 by malee             #+#    #+#             */
/*   Updated: 2025/03/04 22:24:04 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_setup_sphere(t_obj_data **obj)
{
	(*obj)->props.t_sphere.radius = (*obj)->props.t_sphere.diameter / 2;
	(*obj)->props.t_sphere.radius_squared = (*obj)->props.t_sphere.radius
		* (*obj)->props.t_sphere.radius;
}

void	ft_setup_plane(t_obj_data **obj)
{
	(*obj)->props.t_plane.distance_from_origin = ft_vect_dot((*obj)->cord,
			(*obj)->dir);
}

void	ft_setup_cylinder(t_obj_data **obj)
{
	t_vect	axis_vector;

	(*obj)->props.t_cylinder.radius = (*obj)->props.t_cylinder.diameter / 2.0;
	(*obj)->props.t_cylinder.radius_squared = (*obj)->props.t_cylinder.radius
		* (*obj)->props.t_cylinder.radius;
	(*obj)->props.t_cylinder.half_height = (*obj)->props.t_cylinder.height
		/ 2.0;
	axis_vector = ft_vect_mul_all((*obj)->dir,
			(*obj)->props.t_cylinder.half_height);
	(*obj)->props.t_cylinder.top_cap = ft_vect_add((*obj)->cord, axis_vector);
	(*obj)->props.t_cylinder.bottom_cap = ft_vect_sub((*obj)->cord,
			axis_vector);
}

void	ft_setup_cone(t_obj_data **obj)
{
	double length;

	(*obj)->props.t_cone.radius = (*obj)->props.t_cone.diameter / 2.0;
	(*obj)->props.t_cone.half_height = (*obj)->props.t_cone.height / 2.0;
	(*obj)->props.t_cone.slope = (*obj)->props.t_cone.radius
		/ (*obj)->props.t_cone.height;
	(*obj)->props.t_cone.apex = ft_vect_add((*obj)->cord,
			ft_vect_mul_all((*obj)->dir, (*obj)->props.t_cone.height));
	length = sqrt((*obj)->props.t_cone.radius * (*obj)->props.t_cone.radius
			+ (*obj)->props.t_cone.height * (*obj)->props.t_cone.height);
	(*obj)->props.t_cone.cos_apex = (*obj)->props.t_cone.height / length;
}