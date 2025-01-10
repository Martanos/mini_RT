/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvect.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:25:47 by malee             #+#    #+#             */
/*   Updated: 2025/01/10 17:39:35 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVECT_H
# define LIBVECT_H

# include <math.h>

/*
** @brief Vector structure
** @param x The x coordinate of the vector as a double
** @param y The y coordinate of the vector as a double
** @param z The z coordinate of the vector as a double
*/
typedef struct s_vect
{
	double	x;
	double	y;
	double	z;
}			t_vect;

t_vect		ft_vect_add(t_vect a, t_vect b);
t_vect		ft_vect_sub(t_vect a, t_vect b);
t_vect		ft_vect_mul(t_vect a, t_vect b);
t_vect		ft_vect_div(t_vect a, t_vect b);
t_vect		ft_vect_add_all(t_vect a, double scalar);
t_vect		ft_vect_sub_all(t_vect a, double scalar);
t_vect		ft_vect_mul_all(t_vect a, double scalar);
t_vect		ft_vect_div_all(t_vect a, double scalar);
t_vect		ft_vect_norm(t_vect a);
t_vect		ft_vect_cross(t_vect a, t_vect b);
t_vect		ft_vect_dot(t_vect a, t_vect b);
t_vect		ft_vect_create(double x, double y, double z);
double		ft_vect_len(t_vect a);

#endif
