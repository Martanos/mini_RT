/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cone_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:08:00 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/07 18:07:39 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

/**
 * @brief Calculates the height on the cone for a given point
 * @param point The point to calculate height for
 * @param cone The cone object
 * @return The height on the cone
 */
double	get_cone_height(t_vect point, t_cone *cone)
{
	t_vect	cp;

	cp = ft_vect_sub(point, cone->cord);
	return (ft_vect_dot(cp, ft_vect_norm(cone->norm)));
}

/**
 * @brief Calculates the radial direction from axis to surface
 * @param point The point on the cone surface
 * @param axis_point The point on the cone's axis
 * @return The normalized radial direction
 */
t_vect	get_radial_direction(t_vect point, t_vect axis_point)
{
	return (ft_vect_norm(ft_vect_sub(point, axis_point)));
}

/**
 * @brief Calculates the radius at a specific height on the cone
 * @param cone The cone object
 * @param height The height at which to calculate the radius
 * @return The radius at the specified height
 */
double	get_radius_at_height(t_cone *cone, double height)
{
	double	radius;

	radius = cone->diameter / 2.0;
	return ((cone->height - height) * radius / cone->height);
}

/**
 * @brief Calculates the expected point on the cone surface
 * @param axis_point The point on the cone's axis
 * @param radial The radial direction from axis to surface
 * @param radius_at_height The radius at the current height
 * @return The expected point on the cone surface
 */
t_vect	get_expected_point(t_vect axis_point, t_vect radial,
	double radius_at_height)
{
	return (ft_vect_add(axis_point,
			ft_vect_mul_all(radial, radius_at_height)));
}
