/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:15:00 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/19 17:55:58 by seayeo           ###   ########.fr       */
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
 *         -1.0 otherwise
 */
static double	check_height(t_ray ray, double t, t_cone *cone)
{
	t_vect	intersection;
	t_vect	p_minus_o;
	double	height_proj;

	if (t <= 0)
		return (-1.0);
	intersection = ft_vect_add(ray.origin, ft_vect_mul_all(ray.direction, t));
	p_minus_o = ft_vect_sub(intersection, cone->cord);
	height_proj = ft_vect_dot(p_minus_o, cone->norm);
	if (height_proj >= 0 && height_proj <= cone->height)
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
	double	a;
	double	b;
	double	c;
	t_vect	ro_minus_o;
	double	rd_dot_v;
	double	ro_o_dot_v;
	double	discriminant;
	double	t1;
	double	t2;
	double	t1_valid;
	double	t2_valid;

	// Calculate cone's angle
	double radius = cone->diameter / 2.0;
	double k = pow(radius / cone->height, 2);  // squared tan of half-angle
	
	// Calculate vectors for intersection
	ro_minus_o = ft_vect_sub(ray.origin, cone->cord);
	rd_dot_v = ft_vect_dot(ray.direction, cone->norm);
	ro_o_dot_v = ft_vect_dot(ro_minus_o, cone->norm);
	
	// Calculate quadratic coefficients
	a = ft_vect_dot(ray.direction, ray.direction) - (1.0 + k) * pow(rd_dot_v, 2);
	b = 2.0 * (ft_vect_dot(ray.direction, ro_minus_o) - (1.0 + k) * rd_dot_v * ro_o_dot_v);
	c = ft_vect_dot(ro_minus_o, ro_minus_o) - (1.0 + k) * pow(ro_o_dot_v, 2);

	// Solve quadratic equation
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	if (discriminant == 0)
		return (-b / (2 * a));
	t1 = (-b + sqrt(discriminant)) / (2 * a);
	t2 = (-b - sqrt(discriminant)) / (2 * a);
	t1_valid = check_height(ray, t1, cone);
	t2_valid = check_height(ray, t2, cone);

	if (t1_valid > 0 && t2_valid > 0)
		return (fmin(t1_valid, t2_valid));
	else if (t1_valid > 0)
		return (t1_valid);
	else if (t2_valid > 0)
		return (t2_valid);
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
	t_plane	base;
	t_vect	base_center;
	t_vect	normalized_normal;

	normalized_normal = ft_vect_norm(cone->norm);
	// normalized_normal = ft_vect_mul_all(normalized_normal, -1);
	base_center = ft_vect_add(cone->cord, ft_vect_mul_all(normalized_normal,
				cone->height));
	base.cord = base_center;
	base.norm = normalized_normal;
	base.radius = cone->diameter / 2.0;
	base.pro = cone->pro;
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
	if (cone->norm.y < 0)
		cone->norm = ft_vect_mul_all(cone->norm, -1);
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
 *
 * This function:
 * 1. Calculates exact intersection point using ray equation
 * 2. Determines if hit point is on base or conical surface
 * 3. For base hits: Uses inverted cone axis as normal
 * 4. For surface hits: Computes normal using:
 *    - Radial component (perpendicular to axis)
 *    - Axial component (along cone axis)
 *    - Combines them based on cone angle for correct surface normal
 */
void	calculate_cone_hit(t_ray ray, t_cone_collision collision,
		t_hit_record *rec)
{
	t_vect	cp;
	t_vect	normalized_normal;
	double	proj;
	double	height;

	rec->t = collision.closest_t;
	rec->point = ft_vect_add(ray.origin, ft_vect_mul_all(ray.direction,
				collision.closest_t));
	// Vector from apex to intersection point
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
		// Calculate normal at intersection point
		height = proj;
		t_vect p = ft_vect_add(collision.closest_cone->cord,
				ft_vect_mul_all(collision.closest_cone->norm, height));
		
		// Calculate normal using point-to-axis vector and cone slope
		double radius_at_height = (collision.closest_cone->diameter / 2.0) 
			* (height / collision.closest_cone->height);
		t_vect axis_to_point = ft_vect_sub(rec->point, p);
		rec->normal = ft_vect_norm(ft_vect_sub(
			axis_to_point,
			ft_vect_mul_all(collision.closest_cone->norm, radius_at_height 
				/ collision.closest_cone->height)));
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
	double				t;
	t_cone_collision	result;
	t_cone				*cone;

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
