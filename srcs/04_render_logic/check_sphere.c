/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:40:56 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/12 15:12:49 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

/**
 * @brief Calculates quadratic equation coefficients for sphere-ray intersection
 * @param ray The ray to check intersection with
 * @param sphere The sphere to check intersection with
 * @param[out] coef Array to store coefficients where:
 *   - coef[0] = a = dot(direction, direction)
 *   - coef[1] = b = 2 * dot(direction, oc) where oc is origin to center vector
 *   - coef[2] = c = dot(oc, oc) - radius²
 */
static void	get_sphere_quadratic(t_ray ray, t_sphere *sphere,
	double *coef)
{
	t_vect	oc;
	double	radius;

	oc = ft_vect_sub(ray.origin, sphere->cord);
	radius = sphere->diameter / 2.0;
	coef[0] = ft_vect_dot(ray.direction, ray.direction);
	coef[1] = 2.0 * ft_vect_dot(ray.direction, oc);
	coef[2] = ft_vect_dot(oc, oc) - (radius * radius);
}

/**
 * @brief Solves quadratic equation at² + bt + c = 0
 * @param coef Array containing coefficients [a, b, c]
 * @return Smallest positive t for closest intersection point,
 * or -1.0 if no valid intersection exists
 * Calculate smaller root first (closer intersection)
 * If smaller root is behind camera, calculate larger root
 */
static double	solve_sphere_quadratic(double *coef)
{
	double	discriminant;
	double	t;

	discriminant = coef[1] * coef[1] - 4 * coef[0] * coef[2];
	if (discriminant < 0)
		return (-1.0);
	t = (-coef[1] - sqrt(discriminant)) / (2.0 * coef[0]);
	if (t > 0.0)
		return (t);
	t = (-coef[1] + sqrt(discriminant)) / (2.0 * coef[0]);
	if (t > 0.0)
		return (t);
	return (-1.0);
}

/**
 * @brief Checks if a ray intersects with a sphere
 * @param ray The ray to check intersection with
 * @param sphere The sphere to check intersection with
 * @return Distance to intersection point, or -1.0 if no intersection
 */
double	check_sphere_collision(t_ray ray, t_sphere *sphere)
{
	double	coef[3];

	get_sphere_quadratic(ray, sphere, coef);
	return (solve_sphere_quadratic(coef));
}

/**
 * @brief Finds the closest sphere that intersects with the given ray
 * @param ray The ray to check intersections with
 * @param master The master structure containing sphere list
 * @return t_sphere_collision struct containing closest sphere and distance
 */
t_sphere_collision	find_closest_sphere(t_ray ray, t_master *master)
{
	t_sphere_collision	result;
	t_sphere			*sphere;
	double				t;

	result.closest_t = INFINITY;
	result.closest_sphere = NULL;
	sphere = master->sphere_head;
	while (sphere)
	{
		t = check_sphere_collision(ray, sphere);
		if (t > 0.0 && t < result.closest_t)
		{
			result.closest_t = t;
			result.closest_sphere = sphere;
			if (t < EPSILON)
				break ;
		}
		sphere = sphere->next;
	}
	return (result);
}

/**
 * @brief Calculates intersection point and surface normal for a sphere hit
 * @param ray The ray that hit the sphere
 * @param collision The sphere collision data
 * @param[out] rec Hit record to update with intersection details
 */
void	calculate_sphere_hit(t_ray ray, t_sphere_collision collision,
	t_hit_record *rec)
{
	rec->t = collision.closest_t;
	rec->point = ft_vect_add(ray.origin,
			ft_vect_mul_all(ray.direction, collision.closest_t));
	rec->normal = ft_vect_norm(ft_vect_sub(rec->point,
				collision.closest_sphere->cord));
}
