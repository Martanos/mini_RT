/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:30:30 by malee             #+#    #+#             */
/*   Updated: 2025/01/10 17:37:38 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"

/*
** @brief Normalize a vector
** @param a The vector
** @return The normalized vector
*/
t_vect	ft_vect_norm(t_vect a)
{
	double	mag;

	mag = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return ((t_vect){a.x / mag, a.y / mag, a.z / mag});
}

/*
** @brief Cross product of two vectors
** @param a The first vector
** @param b The second vector
** @return cross product of the two vectors store in a new vector struct
*/
t_vect	ft_vect_cross(t_vect a, t_vect b)
{
	return ((t_vect){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
		- a.y * b.x});
}

/*
** @brief Dot product of two vectors
** @param a The first vector
** @param b The second vector
** @return The dot product of the two vectors
*/
double	ft_vect_dot(t_vect a, t_vect b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*
** @brief Length of a vector
** @param a The vector
** @return The length of the vector
*/
double	ft_vect_len(t_vect a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

/*
** @brief Angle between two vectors
** @param a The first vector
** @param b The second vector
** @return The angle between the two vectors
*/
double	ft_vect_angle(t_vect a, t_vect b)
{
	return (acos(ft_vect_dot(a, b) / (ft_vect_len(a) * ft_vect_len(b))));
}
