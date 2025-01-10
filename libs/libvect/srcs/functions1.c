/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:26:48 by malee             #+#    #+#             */
/*   Updated: 2025/01/10 17:36:37 by malee            ###   ########.fr       */
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
	return ((t_vect){x, y, z});
}

/*
** @brief Add two vectors
** @param a The first vector
** @param b The second vector
** @return The sum of the two vectors
*/
t_vect	ft_vect_add(t_vect a, t_vect b)
{
	return ((t_vect){a.x + b.x, a.y + b.y, a.z + b.z});
}

/*
** @brief Subtract two vectors
** @param a The first vector
** @param b The second vector
** @return The difference of the two vectors
*/
t_vect	ft_vect_sub(t_vect a, t_vect b)
{
	return ((t_vect){a.x - b.x, a.y - b.y, a.z - b.z});
}

/*
** @brief Multiply a vector by a scalar
** @param a The vector
** @param b The scalar
** @return The product of the vector and the scalar
*/
t_vect	ft_vect_mul(t_vect a, t_vect b)
{
	return ((t_vect){a.x * b.x, a.y * b.y, a.z * b.z});
}

/*
** @brief Divide a vector by a scalar
** @param a The vector
** @param b The scalar
** @return The quotient of the vector and the scalar
*/
t_vect	ft_vect_div(t_vect a, t_vect b)
{
	return ((t_vect){a.x / b.x, a.y / b.y, a.z / b.z});
}
