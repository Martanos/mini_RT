/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_basics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 01:31:50 by malee             #+#    #+#             */
/*   Updated: 2025/01/21 15:12:02 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"

/*
** @brief Create a vector
** @param x The x coordinate of the vector
** @param y The y coordinate of the vector
** @param z The z coordinate of the vector
** @return A pointer to a new vector struct
*/
t_vect	ft_vect_create(double x, double y, double z)
{
	t_vect	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

/*
** @brief Add two vectors
** @param a The first vector
** @param b The second vector
** @return The sum of the two vectors
*/
t_vect	ft_vect_add(t_vect a, t_vect b)
{
	t_vect	v;

	v.x = a.x + b.x;
	v.y = a.y + b.y;
	v.z = a.z + b.z;
	return (v);
}

/*
** @brief Subtract two vectors
** @param a The first vector
** @param b The second vector
** @return The difference of the two vectors
*/
t_vect	ft_vect_sub(t_vect a, t_vect b)
{
	t_vect	v;

	v.x = a.x - b.x;
	v.y = a.y - b.y;
	v.z = a.z - b.z;
	return (v);
}

/*
** @brief Multiply a vector by a scalar
** @param a The vector
** @param b The scalar
** @return The product of the vector and the scalar
*/
t_vect	ft_vect_mul(t_vect a, t_vect b)
{
	t_vect	v;

	v.x = a.x * b.x;
	v.y = a.y * b.y;
	v.z = a.z * b.z;
	return (v);
}

/*
** @brief Divide a vector by a scalar
** @param a The vector
** @param b The scalar
** @return The quotient of the vector and the scalar
*/
t_vect	ft_vect_div(t_vect a, t_vect b)
{
	t_vect	v;

	v.x = a.x / b.x;
	v.y = a.y / b.y;
	v.z = a.z / b.z;
	return (v);
}
