/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 20:17:36 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 06:57:34 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_sphere_intersection_equation(t_scene **scene, t_obj_data *sphere,
		t_quadratic *quad)
{
	t_vect	oc;

	oc = ft_vect_sub((*scene)->ray_buffer->origin, sphere->cord);
	quad->a = ft_vect_dot((*scene)->ray_buffer->direction,
			(*scene)->ray_buffer->direction);
	quad->b = 2.0 * ft_vect_dot(oc, (*scene)->ray_buffer->direction);
	quad->c = ft_vect_dot(oc, oc) - sphere->props.t_sphere.radius_squared;
	quad->discriminant = quad->b * quad->b - 4 * quad->a * quad->c;
	if (quad->discriminant < 0)
		return (false);
	quad->t1 = (-quad->b - sqrt(quad->discriminant)) / (2.0 * quad->a);
	quad->t2 = (-quad->b + sqrt(quad->discriminant)) / (2.0 * quad->a);
	return (true);
}

static bool	ft_quadratic_find_closest_t(t_scene **scene, t_obj_data *sphere,
		t_quadratic *quad)
{
	if (quad->t1 >= (*scene)->ray_buffer->t_min
		&& quad->t1 <= (*scene)->ray_buffer->t_max
		&& quad->t1 < (*scene)->z_buffer->t)
	{
		(*scene)->z_buffer->t = quad->t1;
		return (true);
	}
	if (quad->t2 >= (*scene)->ray_buffer->t_min
		&& quad->t2 <= (*scene)->ray_buffer->t_max
		&& quad->t2 < (*scene)->z_buffer->t)
	{
		(*scene)->z_buffer->t = quad->t2;
		return (true);
	}
	return (false);
}

static void	ft_calculate_sphere_uv(t_scene **scene)
{
	t_vect	normal;
	double	phi;
	double	theta;

	if ((*scene)->z_buffer->front_face)
		normal = (*scene)->z_buffer->normal;
	else
		normal = ft_vect_mul_all((*scene)->z_buffer->normal, -1);
	phi = atan2(normal.z, normal.x);
	theta = asin(normal.y);
	(*scene)->z_buffer->u = 1 - (phi + M_PI) / (2 * M_PI);
	(*scene)->z_buffer->v = (theta + M_PI / 2) / M_PI;
}

static void	ft_sphere_update_hit_record(t_scene **scene, t_obj_data *sphere,
		t_quadratic *quad)
{
	(*scene)->z_buffer->t = quad->t;
	(*scene)->z_buffer->point = ft_vect_add((*scene)->ray_buffer->origin,
			ft_vect_mul_all((*scene)->ray_buffer->direction, quad->t));
	(*scene)->z_buffer->normal = ft_vect_norm(ft_vect_sub((*scene)->z_buffer->point,
				sphere->cord));
	(*scene)->z_buffer->object = sphere;
	(*scene)->z_buffer->front_face = ft_vect_dot((*scene)->ray_buffer->direction,
			(*scene)->z_buffer->normal) < 0;
	if (!(*scene)->z_buffer->front_face)
		(*scene)->z_buffer->normal = ft_vect_mul_all((*scene)->z_buffer->normal,
				-1);
	ft_calculate_sphere_uv(scene);
}

bool	ft_intersect_sphere(t_scene **scene, t_obj_data *sphere)
{
	t_quadratic	quad;

	quad = (t_quadratic){0};
	if (!ft_sphere_intersection_equation(scene, sphere, &quad))
		return (false);
	if (!ft_quadratic_find_closest_t(scene, sphere, &quad))
		return (false);
	ft_sphere_update_hit_record(scene, sphere, &quad);
	return (true);
}
