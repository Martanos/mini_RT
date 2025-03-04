/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:17:36 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 01:37:34 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_intersect_sphere(t_scene **scene, t_obj_data *sphere)
{
	t_vect	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;

	oc = ft_vect_sub((*scene)->ray_buffer[0].origin, sphere->cord);
	a = ft_vect_dot((*scene)->ray_buffer[0].direction,
			(*scene)->ray_buffer[0].direction);
	b = 2.0 * ft_vect_dot(oc, (*scene)->ray_buffer[0].direction);
	c = ft_vect_dot(oc, oc) - sphere->props.t_sphere.radius_squared;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t < (*scene)->ray_buffer[0].t_min || t > (*scene)->ray_buffer[0].t_max
		|| t >= (*scene)->z_buffer[0].t)
	{
		t = (-b + sqrt(discriminant)) / (2.0 * a);
		if (t < (*scene)->ray_buffer[0].t_min
			|| t > (*scene)->ray_buffer[0].t_max
			|| t >= t >= (*scene)->z_buffer[0].t)
			return (false);
	}
	hit->t = t;
	hit->point = ft_vect_add(ray->origin, ft_vect_mul_all(ray->direction, t));
	hit->normal = ft_vect_norm(ft_vect_sub(hit->point, sphere->cord));
	hit->object = sphere;
	// Determine if we hit the front face or back face
	hit->front_face = ft_vect_dot(ray->direction, hit->normal) < 0;
	if (!hit->front_face)
		hit->normal = ft_vect_mul_all(hit->normal, -1);
	return (true);
}
