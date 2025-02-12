/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:15:00 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/12 15:12:15 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

/**
 * @brief Checks if a ray-cone intersection point lies within the cone's height bounds
 *
 * @param ray The ray being cast in the scene
 * @param t The parameter value at which the ray intersects the cone
 * @param cone Pointer to the cone object being checked
 * @return double Returns the parameter t if intersection is within bounds,
	-1.0 otherwise
 */
static double	check_height(t_ray ray, double t, t_cone *cone)
{
	t_vect	intersection;
	t_vect	v;
	double	height;
	t_vect	normalized_normal;

	intersection = ft_vect_add(ray.origin, ft_vect_mul_all(ray.direction, t));
	v = ft_vect_sub(intersection, cone->cord);
	normalized_normal = ft_vect_norm(cone->norm);
	height = ft_vect_dot(v, normalized_normal);
	if (height >= 0 && height <= cone->height)
		return (t);
	return (-1.0);
}

/**
 * @brief Checks for intersection between a ray and the conical surface
 *
 * @param ray The ray being cast in the scene
 * @param cone Pointer to the cone object to check intersection with
 * @return double Returns the closest valid intersection parameter t, or
	-1.0 if no intersection
 */
static double	check_cone_surface(t_ray ray, t_cone *cone)
{
	t_vect	oc;
	double	radius;
	double	cos_angle;
	t_vect	normalized_normal;
	double	dot_dir_axis;
	double	dot_oc_axis;
	double	discriminant;
	double	t1;
	double	t2;
	double	a;
	double	b;
	double	c;

	oc = ft_vect_sub(ray.origin, cone->cord);
	normalized_normal = ft_vect_norm(cone->norm);
	radius = cone->diameter / 2.0;
	cos_angle = cos(atan(radius / cone->height));
	dot_dir_axis = ft_vect_dot(ray.direction, normalized_normal);
	dot_oc_axis = ft_vect_dot(oc, normalized_normal);
	a = ft_vect_dot(ray.direction, ray.direction) - (1.0 + cos_angle * cos_angle)
		* dot_dir_axis * dot_dir_axis;
	b = 2.0 * (ft_vect_dot(ray.direction, oc) - (1.0 + cos_angle * cos_angle)
			* dot_dir_axis * dot_oc_axis);
	c = ft_vect_dot(oc, oc) - (1.0 + cos_angle * cos_angle) * dot_oc_axis
		* dot_oc_axis;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > 0.0)
	{
		t1 = check_height(ray, t1, cone);
		if (t1 > 0.0)
			return (t1);
	}
	if (t2 > 0.0)
	{
		t2 = check_height(ray, t2, cone);
		if (t2 > 0.0)
			return (t2);
	}
	return (-1.0);
}

/**
 * @brief Checks for intersection between a ray and the cone's base
 *
 * @param ray The ray being cast in the scene
 * @param cone Pointer to the cone object to check intersection with
 * @return double Returns the intersection parameter t, or
	-1.0 if no intersection
 */
static double	check_cone_base(t_ray ray, t_cone *cone)
{
	t_vect	normalized_normal;
	t_vect	base_normal;
	t_plane	base;

	normalized_normal = ft_vect_norm(cone->norm);
	base_normal = ft_vect_mul_all(normalized_normal, -1);
	base.cord = cone->cord;
	base.norm = base_normal;
	base.radius = cone->diameter / 2.0;
	return (check_plane_collision(ray, &base));
}

/**
 * @brief Main function to check for any intersection between a ray and a cone
 *
 * @param ray The ray being cast in the scene
 * @param cone Pointer to the cone object to check intersection with
 * @return double Returns the closest valid intersection parameter t, or
	-1.0 if no intersection
 */
double	check_cone_collision(t_ray ray, t_cone *cone)
{
	double	t_surface;
	double	t_base;
	double	closest_t;

	closest_t = INFINITY;
	t_surface = check_cone_surface(ray, cone);
	t_base = check_cone_base(ray, cone);
	if (t_surface > 0.0 && t_surface < closest_t)
		closest_t = t_surface;
	if (t_base > 0.0 && t_base < closest_t)
		closest_t = t_base;
	if (closest_t == INFINITY)
		return (-1.0);
	return (closest_t);
}

/**
 * @brief Calculates intersection details for a cone hit
 *
 * @param ray The ray that intersected the cone
 * @param collision Structure containing intersection information
 * @param rec Pointer to hit record structure to store intersection details
 */
void	calculate_cone_hit(t_ray ray, t_cone_collision collision,
		t_hit_record *rec)
{
	t_vect	cp;
	t_vect	normalized_normal;
	double	proj;
	double	height;
	t_vect	axis_point;
	t_vect	radial;
	double	cos_angle;

	rec->t = collision.closest_t;
	rec->point = ft_vect_add(ray.origin, ft_vect_mul_all(ray.direction,
				collision.closest_t));
	cp = ft_vect_sub(rec->point, collision.closest_cone->cord);
	normalized_normal = ft_vect_norm(collision.closest_cone->norm);
	proj = ft_vect_dot(cp, normalized_normal);
	if (fabs(proj) < 1e-6)
	{
		// Hit is on base
		rec->normal = ft_vect_mul_all(normalized_normal, -1);
	}
	else
	{
		// Hit is on conical surface
		height = proj;
		axis_point = ft_vect_add(collision.closest_cone->cord,
				ft_vect_mul_all(normalized_normal, height));
		radial = ft_vect_norm(ft_vect_sub(rec->point, axis_point));
		cos_angle = cos(atan(collision.closest_cone->diameter / (2.0
						* collision.closest_cone->height)));
		rec->normal = ft_vect_norm(ft_vect_add(ft_vect_mul_all(radial, cos_angle),
					ft_vect_mul_all(normalized_normal, sin(acos(cos_angle)))));
	}
}

/**
 * @brief Finds the closest cone intersection for a given ray
 *
 * @param ray The ray being cast in the scene
 * @param master Pointer to the master structure containing all scene objects
 * @return t_cone_collision Returns a structure containing the closest intersection
 *         parameter and pointer to the intersected cone
 */
t_cone_collision	find_closest_cone(t_ray ray, t_master *master)
{
	double			t;
	t_cone_collision	result;
	t_cone			*cone;

	result.closest_t = INFINITY;
	result.closest_cone = NULL;
	cone = master->cone_head;
	while (cone)
	{
		t = check_cone_collision(ray, cone);
		if (t > 0.0 && t < result.closest_t)
		{
			result.closest_t = t;
			result.closest_cone = cone;
			if (t < EPSILON)
				break ;
		}
		cone = cone->next;
	}
	return (result);
}
