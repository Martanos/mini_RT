/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cone_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:05:00 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/07 18:03:06 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

/**
 * @brief Checks if a ray intersects with a cone
 * @param ray The ray to check intersection with
 * @param cone Pointer to the cone object to check intersection with
 * @return Distance to intersection point, or -1.0 if no intersection
 */
double	check_cone_collision(t_ray ray, t_cone *cone)
{
	double	t_surface;
	double	closest_t;

	closest_t = INFINITY;
	t_surface = check_cone_surface(ray, cone);
	if (t_surface > 0.0 && t_surface < closest_t)
		closest_t = t_surface;
	if (closest_t == INFINITY)
		return (-1.0);
	return (closest_t);
}

/**
 * @brief Finds the closest cone that intersects with the given ray
 * @param ray The ray to check intersections with
 * @param master The master structure containing cone list
 * @return t_cone_collision struct containing closest cone and distance
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

/**
 * @brief Calculates intersection point and surface normal for a cone hit
 * @param ray The ray that hit the cone
 * @param collision The cone collision data
 * @param[out] rec Hit record to update with intersection details
 */
void	calculate_cone_hit(t_ray ray, t_cone_collision collision,
	t_hit_record *rec)
{
	t_vect	cp;
	t_vect	normalized_normal;
	double	height;
	t_vect	axis_point;

	rec->t = collision.closest_t;
	rec->point = get_cone_intersection_point(ray, collision.closest_t);
	cp = ft_vect_sub(rec->point, collision.closest_cone->cord);
	normalized_normal = ft_vect_norm(collision.closest_cone->norm);
	height = ft_vect_dot(cp, normalized_normal);
	axis_point = ft_vect_add(collision.closest_cone->cord,
			ft_vect_mul_all(normalized_normal, height));
	get_cone_normal(rec, ray, collision.closest_cone, axis_point);
}
