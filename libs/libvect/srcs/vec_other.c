/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_other.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:30:30 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 21:03:03 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"

/*
** @brief Normalize a vector to a unit vector returning the original vector if
** the magnitude is too small to normalize
** @param a The vector
** @return The normalized vector
*/
t_vect	ft_vect_norm(t_vect a)
{
	double	mag;

	mag = ft_vect_mag(a);
	if (mag > 0.000001)
		return (ft_vect_div_all(a, mag));
	return (a);
}

/*
** @brief Cross product of two vectors
** @param a The first vector
** @param b The second vector
** @return cross product of the two vectors store in a new vector struct
*/
t_vect	ft_vect_cross(t_vect a, t_vect b)
{
	t_vect	v;

	v.x = a.y * b.z - a.z * b.y;
	v.y = a.z * b.x - a.x * b.z;
	v.z = a.x * b.y - a.y * b.x;
	return (v);
}

/*
** @brief Dot product of two vectors
** @param a The first vector
** @param b The second vector
** @return The dot product of the two vectors
*/
double	ft_vect_dot(t_vect a, t_vect b)
{
	double	dot;

	dot = a.x * b.x + a.y * b.y + a.z * b.z;
	return (dot);
}

/*
** @brief Magnitude of a vector
** @param a The vector
** @return The magnitude of the vector
*/
double	ft_vect_mag(t_vect a)
{
	double	mag;

	mag = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (mag);
}

/*
** @brief Angle between two vectors
** @param a The first vector
** @param b The second vector
** @return The angle between the two vectors
*/
double	ft_vect_angle(t_vect a, t_vect b)
{
	double	dot;
	double	mag_a;
	double	mag_b;
	double	angle;

	dot = ft_vect_dot(a, b);
	mag_a = ft_vect_mag(a);
	mag_b = ft_vect_mag(b);
	angle = acos(dot / (mag_a * mag_b));
	return (angle);
}
