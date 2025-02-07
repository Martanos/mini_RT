/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:48:07 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/07 14:57:54 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void get_sphere_uv(t_vect point, double *u, double *v)
{
    *u = 0.5 + (atan2(point.z, point.x) / (2 * M_PI));
    *v = 0.5 - (asin(point.y) / M_PI);
}

void get_plane_uv(t_vect point, t_plane *plane, double *u, double *v)
{
    t_vect right;
    t_vect up;
    t_vect up_vector;

    up_vector = ft_vect_create(0, 1, 0);
    right = ft_vect_cross(up_vector, plane->norm);
    up = ft_vect_cross(plane->norm, right);

    right = ft_vect_norm(right);
    up = ft_vect_norm(up);

    *u = ft_vect_dot(point, right);
    *v = ft_vect_dot(point, up);

    *u = fmod(*u, 1.0);
    *v = fmod(*v, 1.0);
    if (*u < 0)
        *u += 1.0;
    if (*v < 0)
        *v += 1.0;
}

void get_cylinder_uv(t_vect point, t_cylinder *cylinder, double *u, double *v)
{
    t_vect local_point;
    t_vect up_vector;
    t_vect temp_cross;
    t_vect double_cross;
    double angle;

    up_vector = ft_vect_create(0, 1, 0);
    local_point = ft_vect_sub(point, cylinder->cord);

    *v = ft_vect_dot(local_point, cylinder->norm) / cylinder->height;
    *v = fmod(*v, 1.0);
    if (*v < 0)
        *v += 1.0;

    temp_cross = ft_vect_cross(cylinder->norm, up_vector);
    double_cross = ft_vect_cross(cylinder->norm, temp_cross);

    angle = atan2(ft_vect_dot(local_point, temp_cross),
                  ft_vect_dot(local_point, double_cross));
    *u = 0.5 + (angle / (2 * M_PI));
}

void get_cone_uv(t_vect point, t_cone *cone, double *u, double *v)
{
    t_vect local_point;
    t_vect up_vector;
    t_vect temp_cross;
    t_vect double_cross;
    double angle;
    double height_ratio;

    up_vector = ft_vect_create(0, 1, 0);
    local_point = ft_vect_sub(point, cone->cord);

    height_ratio = ft_vect_dot(local_point, cone->norm) / cone->height;
    *v = height_ratio;
    *v = fmod(*v, 1.0);
    if (*v < 0)
        *v += 1.0;

    temp_cross = ft_vect_cross(cone->norm, up_vector);
    double_cross = ft_vect_cross(cone->norm, temp_cross);

    angle = atan2(ft_vect_dot(local_point, temp_cross),
                  ft_vect_dot(local_point, double_cross));
    *u = 0.5 + (angle / (2 * M_PI));
}
