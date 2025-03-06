/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:17:36 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 14:11:19 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_sphere_intersection_equation(t_ray **ray, t_obj_data *sphere,
		t_quadratic *quad)
{
	t_vect	oc;

	oc = ft_vect_sub((*ray)->origin, sphere->cord);
	quad->a = ft_vect_dot((*ray)->direction, (*ray)->direction);
	quad->b = 2.0 * ft_vect_dot(oc, (*ray)->direction);
	quad->c = ft_vect_dot(oc, oc) - sphere->props.t_sphere.radius_squared;
	quad->discriminant = quad->b * quad->b - 4 * quad->a * quad->c;
	if (quad->discriminant < 0)
		return (false);
	quad->t1 = (-quad->b - sqrt(quad->discriminant)) / (2.0 * quad->a);
	quad->t2 = (-quad->b + sqrt(quad->discriminant)) / (2.0 * quad->a);
	return (true);
}

static void	ft_calculate_sphere_uv(t_hit **hit)
{
	t_vect	normal;
	double	phi;
	double	theta;

	if ((*hit)->front_face)
		normal = (*hit)->normal;
	else
		normal = ft_vect_mul_all((*hit)->normal, -1);
	phi = atan2(normal.z, normal.x);
	theta = asin(normal.y);
	(*hit)->u = 1 - (phi + M_PI) / (2 * M_PI);
	(*hit)->v = (theta + M_PI / 2) / M_PI;
}

static void	ft_sphere_update_hit_record(t_ray **ray, t_hit **hit,
		t_obj_data *sphere, t_quadratic *quad)
{
	(*hit)->point = ft_vect_add((*ray)->origin,
			ft_vect_mul_all((*ray)->direction, quad->t));
	(*hit)->normal = ft_vect_norm(ft_vect_sub((*hit)->point, sphere->cord));
	(*hit)->object = sphere;
	(*hit)->front_face = ft_vect_dot((*ray)->direction, (*hit)->normal) < 0;
	if (!(*hit)->front_face)
		(*hit)->normal = ft_vect_mul_all((*hit)->normal, -1);
	ft_calculate_sphere_uv(hit);
}

bool	ft_intersect_sphere(t_scene **scene, t_obj_data *sphere, t_hit **hit,
		t_ray **ray)
{
	t_quadratic	quad;

	quad = (t_quadratic){0};
	if (!ft_sphere_intersection_equation(ray, sphere, &quad))
		return (false);
	if (!ft_quadratic_find_closest_t(ray, hit, &quad))
		return (false);
	ft_sphere_update_hit_record(ray, hit, sphere, &quad);
	return (true);
}
