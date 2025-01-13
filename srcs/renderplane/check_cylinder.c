/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:18:06 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/13 16:57:16 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"
#include "plane.h"

/**
 * @brief Checks if a ray-cylinder intersection point lies within the cylinder's height bounds
 * 
 * @param ray The ray being cast in the scene
 * @param t The parameter value at which the ray intersects the cylinder
 * @param cylinder Pointer to the cylinder object being checked
 * @return double Returns the parameter t if intersection is within bounds, -1.0 otherwise
 * 
 * This function:
 * 1. Calculates the actual intersection point using the ray equation P = O + tD
 * 2. Finds the vector from cylinder position to intersection point
 * 3. Projects this vector onto cylinder axis to get height
 * 4. Verifies if height is within cylinder's bounds [-height/2, height/2]
 */
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

/**
 * @brief Checks for intersection between a ray and the cylindrical side surface
 * 
 * @param ray The ray being cast in the scene
 * @param cylinder Pointer to the cylinder object to check intersection with
 * @return double Returns the closest valid intersection parameter t, or -1.0 if no intersection
 * 
 * This function:
 * 1. Uses quadratic equation to find intersection with infinite cylinder
 * 2. Calculates discriminant to determine number of intersections
 * 3. If intersections exist, checks both solutions for validity within height bounds
 * 4. Returns the closest valid intersection parameter
 * 
 * The quadratic equation coefficients are derived from:
 * - Vector between ray origin and cylinder position (oc)
 * - Cross products of ray direction and cylinder normal
 * - Cylinder radius (diameter/2)
 */
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

/**
 * @brief Checks for intersection between a ray and the cylinder's end caps
 * 
 * @param ray The ray being cast in the scene
 * @param cylinder Pointer to the cylinder object to check intersection with
 * @return double Returns the closest valid intersection parameter t, or -1.0 if no intersection
 * 
 * This function:
 * 1. Creates two capped planes representing top and bottom caps
 * 2. Positions caps at ±height/2 from cylinder center
 * 3. Checks intersection with both caps using check_capped_plane_collision
 * 4. Returns the closest valid intersection parameter
 * 
 * The caps are circular planes with:
 * - Radius equal to cylinder radius
 * - Normal vectors pointing outward from cylinder
 * - Positions offset from cylinder center by ±height/2
 */
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

/**
 * @brief Main function to check for any intersection between a ray and a cylinder
 * 
 * @param ray The ray being cast in the scene
 * @param cylinder Pointer to the cylinder object to check intersection with
 * @return double Returns the closest valid intersection parameter t, or -1.0 if no intersection
 * 
 * This function:
 * 1. Checks for intersection with cylindrical side surface
 * 2. Checks for intersection with top and bottom caps
 * 3. Returns the closest valid intersection point among all surfaces
 * 
 * Combines results from check_cylinder_side and check_cylinder_caps to find
 * the closest intersection point with any part of the cylinder.
 */
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

/**
 * @brief Finds the closest cylinder intersection for a given ray
 * 
 * @param ray The ray being cast in the scene
 * @param mlx_data Pointer to the main data structure containing scene information
 * @return t_cylinder_collision Returns a structure containing the closest intersection
 *         parameter and pointer to the intersected cylinder
 * 
 * This function:
 * 1. Iterates through all cylinders in the scene
 * 2. Checks intersection with each cylinder
 * 3. Keeps track of the closest intersection found
 * 4. Returns both the intersection parameter and the intersected cylinder
 */
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

/**
 * @brief Calculates intersection details for a cylinder hit
 * 
 * @param ray The ray that intersected the cylinder
 * @param collision Structure containing intersection information
 * @param rec Pointer to hit record structure to store intersection details
 * 
 * This function:
 * 1. Calculates exact intersection point using ray equation
 * 2. Determines if hit point is on caps or cylindrical surface
 * 3. Computes appropriate surface normal at intersection point
 * 4. Stores results in hit record structure
 * 
 * Surface normal calculation:
 * - For caps: Uses cylinder axis direction (top) or its negative (bottom)
 * - For side: Uses normalized vector from cylinder axis to hit point
 */
void	calculate_cylinder_hit(t_ray ray, t_cylinder_collision collision, t_hit_record *rec)
{
	rec->t = collision.closest_t; // Store the intersection parameter
	rec->point = vect_add(ray.origin, vect_multiply(ray.direction, collision.closest_t)); // Calculate the intersection point

		// First, determine if the hit point is on a cap or the cylindrical surface
	t_vect cp = vect_sub(rec->point, collision.closest_cylinder->cylinder_pos);
	t_vect normalized_normal = vect_normalize(collision.closest_cylinder->cylinder_normal);
	double proj = vect_dot(cp, normalized_normal);
	
	// Check if hit point is near either cap (using a small epsilon for floating-point comparison)
	double half_height = collision.closest_cylinder->cylinder_height / 2.0;
	if (fabs(proj - half_height) < 1e-6)
	{
		// Hit is on top cap
		rec->normal = normalized_normal;
	}
	else if (fabs(proj + half_height) < 1e-6)
	{
		// Hit is on bottom cap
		rec->normal = vect_multiply(normalized_normal, -1);
	}
	else
	{
		// Hit is on cylindrical surface
		t_vect axis_point = vect_add(collision.closest_cylinder->cylinder_pos, 
			vect_multiply(normalized_normal, proj));
		rec->normal = vect_normalize(vect_sub(rec->point, axis_point));
	}
}
