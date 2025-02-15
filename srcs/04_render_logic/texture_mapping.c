/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:48:07 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/15 18:50:01 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void get_sphere_uv(t_vect point, double *u, double *v)
{
    t_vect normalized_point;
    double phi;
    double theta;
    
    normalized_point = ft_vect_norm(point);
    phi = atan2(normalized_point.z, normalized_point.x);
    theta = acos(normalized_point.y);
    
    *u = (phi + M_PI) / (2 * M_PI);
    *v = theta / M_PI;
}

void	get_plane_uv(t_vect point, t_plane *plane, double *u, double *v)
{
    t_vect	right;
    t_vect	up;
    t_vect	up_vector;
    t_vect	temp_up;

    up_vector = ft_vect_create(0, 1, 0);
    // Handle case where plane normal is parallel to up_vector
    if (fabs(ft_vect_dot(plane->norm, up_vector)) > 0.99)
        temp_up = ft_vect_create(0, 0, 1);  // Use different reference vector
    else
        temp_up = up_vector;
    right = ft_vect_cross(temp_up, plane->norm);
    if (ft_vect_mag(right) < 1e-6)  // Check if cross product is too small
        right = ft_vect_create(1, 0, 0);  // Use fallback vector
    right = ft_vect_norm(right);
    up = ft_vect_norm(ft_vect_cross(plane->norm, right));
    // Calculate UV coordinates
    *u = ft_vect_dot(point, right);
    *v = ft_vect_dot(point, up);
    // Scale and wrap UV coordinates
    *u = fmod(*u * 0.5, 1.0);
    *v = fmod(*v * 0.5, 1.0);
    if (*u < 0)
        *u += 1.0;
    if (*v < 0)
        *v += 1.0;
}
