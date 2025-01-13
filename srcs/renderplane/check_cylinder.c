/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:18:06 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/13 14:02:16 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "plane.h"

// Helper function to check if the intersection point lies within the height bounds of the cylinder
static double check_height(t_ray ray, double t, t_cylinder_obj *cylinder)
{
    t_vect intersection;
    t_vect v;
    double height;

    // Calculate the intersection point of the ray and the cylinder
    intersection = vect_add(ray.origin, vect_multiply(ray.direction, t));
    
    // Calculate the vector from the cylinder's position to the intersection point
    v = vect_sub(intersection, cylinder->cylinder_pos);

    // Project the vector onto the cylinder's axis (normal)
    t_vect normalized_normal = vect_normalize(cylinder->cylinder_normal);
    height = vect_dot(v, normalized_normal);

    // Check if the intersection point is within the height bounds of the cylinder
    if (height >= -cylinder->cylinder_height / 2 && height <= cylinder->cylinder_height / 2)
        return t;
    return -1.0; // No valid intersection if outside the height bounds
}

// Check if the ray intersects the cylindrical side
static double check_cylinder_side(t_ray ray, t_cylinder_obj *cylinder)
{
    t_vect oc = vect_sub(ray.origin, cylinder->cylinder_pos);
    t_vect normalized_normal = vect_normalize(cylinder->cylinder_normal);
    t_vect cross_dir_normal = vect_cross(ray.direction, normalized_normal);
    t_vect cross_oc_normal = vect_cross(oc, normalized_normal);
    double radius = cylinder->cylinder_diameter / 2.0;

    // Compute the coefficients of the quadratic equation
    double a = vect_dot(cross_dir_normal, cross_dir_normal);
    double b = 2.0 * vect_dot(cross_dir_normal, cross_oc_normal);
    double c = vect_dot(cross_oc_normal, cross_oc_normal) - (radius * radius);

    // Compute the discriminant
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return -1.0; // No intersection if the discriminant is negative

    // Solve the quadratic equation for t
    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    // Check if t1 is a valid intersection
    if (t1 > 0.0)
    {
        t1 = check_height(ray, t1, cylinder); // Check if the intersection lies within the height
        if (t1 > 0.0)
            return t1;
    }

    // Check if t2 is a valid intersection
    if (t2 > 0.0)
    {
        t2 = check_height(ray, t2, cylinder); // Check if the intersection lies within the height
        if (t2 > 0.0)
            return t2;
    }

    return -1.0; // No valid intersection
}

// Check if the ray intersects the caps of the cylinder
static double check_cylinder_caps(t_ray ray, t_cylinder_obj *cylinder)
{
    double t;
    double closest_t = INFINITY;
    t_vect normalized_normal = vect_normalize(cylinder->cylinder_normal);
    t_vect bottom_normal = vect_normalize(vect_multiply(normalized_normal, -1));
    t_vect top_normal = normalized_normal;  // Already normalized

    t_capped_plane bottom_cap = {
        .position = vect_add(cylinder->cylinder_pos,
            vect_multiply(normalized_normal, -cylinder->cylinder_height / 2)),
        .normal = bottom_normal,
        .radius = cylinder->cylinder_diameter / 2.0
    };

    t_capped_plane top_cap = {
        .position = vect_add(cylinder->cylinder_pos, 
            vect_multiply(normalized_normal, cylinder->cylinder_height / 2)),
        .normal = top_normal,
        .radius = cylinder->cylinder_diameter / 2.0
    };

    // Check bottom cap
    t = check_capped_plane_collision(ray, bottom_cap);
    if (t > 0.0)
        closest_t = t;

    // Check top cap
    t = check_capped_plane_collision(ray, top_cap);
    if (t > 0.0 && t < closest_t)
        closest_t = t;

    if (closest_t == INFINITY)
        return (-1.0);
    return (closest_t);
}

// Main function to check for any cylinder intersection
double check_cylinder_collision(t_ray ray, t_cylinder_obj *cylinder)
{
    double t_side, t_caps;
    double closest_t = INFINITY;

    // Check both side and caps intersections
    t_side = check_cylinder_side(ray, cylinder);
    t_caps = check_cylinder_caps(ray, cylinder);

    // Find the closest valid intersection
    if (t_side > 0.0 && t_side < closest_t)
        closest_t = t_side;
    if (t_caps > 0.0 && t_caps < closest_t)
        closest_t = t_caps;

    if (closest_t == INFINITY)
        return (-1.0);
    return (closest_t);
}

// Find the closest cylinder hit for the ray
t_cylinder_collision find_closest_cylinder(t_ray ray, t_data *mlx_data)
{
    double t;
    t_cylinder_collision result;
    t_cylinder_obj *cylinder;
    int i = 0;

    result.closest_t = INFINITY;
    result.closest_cylinder = NULL;
    
    // Iterate through the list of cylinders to find the closest one
    while (mlx_data->instruction_set->cylinder_obj_list[i])
    {
        cylinder = mlx_data->instruction_set->cylinder_obj_list[i];
        t = check_cylinder_collision(ray, cylinder); // Check if the ray intersects the cylinder
        if (t > 0.0 && t < result.closest_t)
        {
            result.closest_t = t; // Update the closest intersection
            result.closest_cylinder = cylinder; // Store the closest cylinder
        }
        i++;
    }

    return result;
}

// Calculate the hit point and normal at the intersection with the cylinder
void calculate_cylinder_hit(t_ray ray, t_cylinder_collision collision, t_hit_record *rec)
{
    rec->t = collision.closest_t; // Store the intersection parameter
    rec->point = vect_add(ray.origin, vect_multiply(ray.direction, collision.closest_t)); // Calculate the intersection point

    // Calculate the normal at the intersection point on the cylinder surface
    t_vect cp = vect_sub(rec->point, collision.closest_cylinder->cylinder_pos);
    t_vect normalized_normal = vect_normalize(collision.closest_cylinder->cylinder_normal);
    double proj = vect_dot(cp, normalized_normal);
    t_vect axis_point = vect_add(collision.closest_cylinder->cylinder_pos, vect_multiply(normalized_normal, proj));
    
    // The normal is the vector from the point on the axis to the intersection point
    rec->normal = vect_normalize(vect_sub(rec->point, axis_point));
}
