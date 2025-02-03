/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:21:38 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/03 21:00:58 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_vect	vect_add(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vect	vect_sub(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

double	vect_magnitude(t_vect v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	vect_dot(t_vect v1, t_vect v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vect	vect_normalize(t_vect v)
{
	double	mag;

	mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= mag;
	v.y /= mag;
	v.z /= mag;
	return (v);
}

t_vect	vect_divide(t_vect v1, double n)
{
	t_vect	v;

	v.x = v1.x / n;
	v.y = v1.y / n;
	v.z = v1.z / n;
	return (v);
}

t_vect	vect_create(double x, double y, double z)
{
	t_vect	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vect	vect_multiply(t_vect v1, double n)
{
	t_vect	v;

	v.x = v1.x * n;
	v.y = v1.y * n;
	v.z = v1.z * n;
	return (v);
}

t_vect	vect_cross(t_vect v1, t_vect v2)
{
	t_vect	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

t_vect	ft_vect_mul_all(t_vect a, double scalar)
{
	return ((t_vect){a.x * scalar, a.y * scalar, a.z * scalar});
}

void	set_face_normal(t_hit_record *rec, const t_ray *r,
		const t_vect *outward_normal)
{
	if (vect_dot(r->direction, *outward_normal) > 0.0)
		rec->normal = vect_multiply(*outward_normal, -1); // Inside
	else
		rec->normal = *outward_normal; // Outside
}
