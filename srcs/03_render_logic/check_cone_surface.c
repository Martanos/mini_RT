/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cone_surface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:05:00 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/07 18:06:13 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

/**
 * @brief Calculates dot products needed for cone intersection
 * @param ray The ray to check intersection with
 * @param cone Pointer to the cone object
 * @param dot_vals Array to store dot product values
 * @param oc Vector from cone origin to ray origin
 */
static void	get_cone_dots(t_ray ray, t_cone *cone, double *dot_vals,
	t_vect oc)
{
	t_vect	normalized_normal;

	normalized_normal = ft_vect_norm(cone->norm);
	dot_vals[0] = ft_vect_dot(ray.direction, normalized_normal);
	dot_vals[1] = ft_vect_dot(oc, normalized_normal);
}

/**
 * @brief Calculates the quadratic equation coefficients for cone intersection
 * @param ray The ray to check intersection with
 * @param cone Pointer to the cone object
 * @param coef Array to store the calculated coefficients
 */
static void	get_cone_quadratic(t_ray ray, t_cone *cone, double *coef)
{
	t_vect	oc;
	double	radius;
	double	k;
	double	dot_vals[2];

	oc = ft_vect_sub(ray.origin, cone->cord);
	radius = cone->diameter / 2.0;
	k = (radius * radius) / (cone->height * cone->height);
	get_cone_dots(ray, cone, dot_vals, oc);
	coef[0] = ft_vect_dot(ray.direction, ray.direction)
		- (1.0 + k) * dot_vals[0] * dot_vals[0];
	coef[1] = 2.0 * (ft_vect_dot(ray.direction, oc)
			- (1.0 + k) * dot_vals[0] * dot_vals[1]);
	coef[2] = ft_vect_dot(oc, oc) - (1.0 + k) * dot_vals[1] * dot_vals[1];
}

/**
 * @brief Checks if a t value is valid for cone intersection
 * @param ray The ray to check intersection with
 * @param t The parameter value to check
 * @param cone Pointer to the cone object
 * @return The valid t value or -1.0 if invalid
 */
static double	check_valid_t(t_ray ray, double t, t_cone *cone)
{
	if (t <= 0.0)
		return (-1.0);
	return (check_height(ray, t, cone));
}

/**
 * @brief Solves the quadratic equation for cone intersection
 * @param coef Array containing the quadratic coefficients
 * @param ray The ray to check intersection with
 * @param cone Pointer to the cone object
 * @return The closest valid intersection parameter t, or -1.0 if no intersection
 */
static double	solve_cone_quadratic(double *coef, t_ray ray, t_cone *cone)
{
	double	discriminant;
	double	t1;
	double	t2;
	double	valid_t1;
	double	valid_t2;

	discriminant = coef[1] * coef[1] - 4 * coef[0] * coef[2];
	if (discriminant < 0)
		return (-1.0);
	t1 = (-coef[1] - sqrt(discriminant)) / (2.0 * coef[0]);
	t2 = (-coef[1] + sqrt(discriminant)) / (2.0 * coef[0]);
	valid_t1 = check_valid_t(ray, t1, cone);
	valid_t2 = check_valid_t(ray, t2, cone);
	if (valid_t1 > 0.0)
		return (valid_t1);
	if (valid_t2 > 0.0)
		return (valid_t2);
	return (-1.0);
}

/**
 * @brief Checks for intersection between a ray and the conical surface
 * @param ray The ray to check intersection with
 * @param cone Pointer to the cone object to check intersection with
 * @return The closest valid intersection parameter t, or -1.0 if no intersection
 */
double	check_cone_surface(t_ray ray, t_cone *cone)
{
	double	coef[3];

	get_cone_quadratic(ray, cone, coef);
	return (solve_cone_quadratic(coef, ray, cone));
}
