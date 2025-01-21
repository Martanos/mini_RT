/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_scalar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:13:25 by malee             #+#    #+#             */
/*   Updated: 2025/01/21 15:14:05 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"

/*
** @brief Add a scalar to all components of a vector
** @param a The vector
** @param scalar The scalar to add
** @return The vector with the scalar added to all components
*/
t_vect	ft_vect_add_all(t_vect a, double scalar)
{
	t_vect	v;

	v.x = a.x + scalar;
	v.y = a.y + scalar;
	v.z = a.z + scalar;
	return (v);
}

/*
** @brief Subtract two vectors
** @param a The vector
** @param scalar The scalar to subtract
** @return The vector with the scalar subtracted from all components
*/
t_vect	ft_vect_sub_all(t_vect a, double scalar)
{
	t_vect	v;

	v.x = a.x - scalar;
	v.y = a.y - scalar;
	v.z = a.z - scalar;
	return (v);
}

/*
** @brief Multiply a vector by a scalar
** @param a The vector
** @param scalar The scalar
** @return The product of the vector and the scalar
*/
t_vect	ft_vect_mul_all(t_vect a, double scalar)
{
	t_vect	v;

	v.x = a.x * scalar;
	v.y = a.y * scalar;
	v.z = a.z * scalar;
	return (v);
}

/*
** @brief Divide a vector by a scalar
** @param a The vector
** @param scalar The scalar
** @return The quotient of the vector and the scalar
*/
t_vect	ft_vect_div_all(t_vect a, double scalar)
{
	t_vect	v;

	v.x = a.x / scalar;
	v.y = a.y / scalar;
	v.z = a.z / scalar;
	return (v);
}
