/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:15:00 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/21 01:25:15 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "plane.h"

/**

	* @brief Checks if a ray-cone intersection point lies within the cone's height bounds
 *
 * @param ray The ray being cast in the scene
 * @param t The parameter value at which the ray intersects the cone
 * @param cone Pointer to the cone object being checked
 * @return double Returns the parameter t if intersection is within bounds,
	-1.0 otherwise
 */
static double	check_height(t_ray ray, double t, t_cone_object *cone)
{
	t_vect	intersection;
	t_vect	v;
	double	height;
	t_vect	normalized_normal;

	intersection = vect_add(ray.origin, vect_multiply(ray.direction, t));
	v = vect_sub(intersection, cone->cone_pos);
	normalized_normal = vect_normalize(cone->cone_normal);
	height = vect_dot(v, normalized_normal);
	if (height >= 0 && height <= cone->cone_height)
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
static double	check_cone_surface(t_ray ray, t_cone_object *cone)
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

	double a, b, c;
	oc = vect_sub(ray.origin, cone->cone_pos);
	normalized_normal = vect_normalize(cone->cone_normal);
	radius = cone->cone_diameter / 2.0;
	cos_angle = cos(atan(radius / cone->cone_height));
	dot_dir_axis = vect_dot(ray.direction, normalized_normal);
	dot_oc_axis = vect_dot(oc, normalized_normal);
	a = vect_dot(ray.direction, ray.direction) - (1.0 + cos_angle * cos_angle)
		* dot_dir_axis * dot_dir_axis;
	b = 2.0 * (vect_dot(ray.direction, oc) - (1.0 + cos_angle * cos_angle)
			* dot_dir_axis * dot_oc_axis);
	c = vect_dot(oc, oc) - (1.0 + cos_angle * cos_angle) * dot_oc_axis
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
static double	check_cone_base(t_ray ray, t_cone_object *cone)
{
	t_vect			normalized_normal;
	t_vect			base_normal;
	t_capped_plane	base = {.position = cone->cone_pos, .normal;

	base = {.position = cone->cone_pos, .normal = base_normal, .radius;
	normalized_normal = vect_normalize(cone->cone_normal);
	base_normal = vect_multiply(normalized_normal, -1);
	base = {.position = cone->cone_pos, .normal = base_normal,
		.radius = cone->cone_diameter / 2.0};
	return (check_capped_plane_collision(ray, base));
}

/**
 * @brief Main function to check for any intersection between a ray and a cone
 *
 * @param ray The ray being cast in the scene
 * @param cone Pointer to the cone object to check intersection with
 * @return double Returns the closest valid intersection parameter t, or
	-1.0 if no intersection
 */
double	check_cone_collision(t_ray ray, t_cone_object *cone)
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
	rec->point = vect_add(ray.origin, vect_multiply(ray.direction,
				collision.closest_t));
	cp = vect_sub(rec->point, collision.closest_cone->cone_pos);
	normalized_normal = vect_normalize(collision.closest_cone->cone_normal);
	proj = vect_dot(cp, normalized_normal);
	if (fabs(proj) < 1e-6)
	{
		// Hit is on base
		rec->normal = vect_multiply(normalized_normal, -1);
	}
	else
	{
		// Hit is on conical surface
		height = proj;
		// double radius = (collision.closest_cone->cone_diameter / 2.0) *
		// 	(1.0 - height / collision.closest_cone->cone_height);
		axis_point = vect_add(collision.closest_cone->cone_pos,
				vect_multiply(normalized_normal, height));
		radial = vect_normalize(vect_sub(rec->point, axis_point));
		cos_angle = cos(atan(collision.closest_cone->cone_diameter / (2.0
						* collision.closest_cone->cone_height)));
		rec->normal = vect_normalize(vect_add(vect_multiply(radial, cos_angle),
					vect_multiply(normalized_normal, sin(acos(cos_angle)))));
	}
}

/**
 * @brief Finds the closest cone intersection for a given ray
 *
 * @param ray The ray being cast in the scene

	* @param mlx_data Pointer to the main data structure containing scene information

	* @return t_cone_collision Returns a structure containing the closest intersection
 *         parameter and pointer to the intersected cone
 */
t_cone_collision	find_closest_cone(t_ray ray, t_data *mlx_data)
{
	double				t;
	t_cone_collision	result;
	t_cone_object		*cone;
	int					i;

	i = 0;
	result.closest_t = INFINITY;
	result.closest_cone = NULL;
	while (mlx_data->instruction_set->cone_obj_list[i])
	{
		cone = mlx_data->instruction_set->cone_obj_list[i];
		t = check_cone_collision(ray, cone);
		if (t > 0.0 && t < result.closest_t)
		{
			result.closest_t = t;
			result.closest_cone = cone;
		}
		i++;
	}
	return (result);
}
