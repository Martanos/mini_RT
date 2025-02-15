/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:18:06 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/12 15:12:07 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

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
static double check_height(t_ray ray, double t, t_cylinder *cylinder)
{
	t_vect intersection;
	t_vect v;
	double height;

	// Calculate the intersection point of the ray and the cylinder
	intersection = ft_vect_add(ray.origin, ft_vect_mul_all(ray.direction, t));
	
	// Calculate the vector from the cylinder's position to the intersection point
	v = ft_vect_sub(intersection, cylinder->cord);

	// Project the vector onto the cylinder's axis (normal)
	t_vect normalized_normal = ft_vect_norm(cylinder->norm);
	height = ft_vect_dot(v, normalized_normal);

	// Check if the intersection point is within the height bounds of the cylinder
	if (height >= -cylinder->height / 2 && height <= cylinder->height / 2)
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
static double check_cylinder_side(t_ray ray, t_cylinder *cylinder)
{
	t_vect oc = ft_vect_sub(ray.origin, cylinder->cord);
	t_vect normalized_normal = ft_vect_norm(cylinder->norm);
	t_vect cross_dir_normal = ft_vect_cross(ray.direction, normalized_normal);
	t_vect cross_oc_normal = ft_vect_cross(oc, normalized_normal);
	double radius = cylinder->diameter / 2.0;

	// Compute the coefficients of the quadratic equation
	double a = ft_vect_dot(cross_dir_normal, cross_dir_normal);
	double b = 2.0 * ft_vect_dot(cross_dir_normal, cross_oc_normal);
	double c = ft_vect_dot(cross_oc_normal, cross_oc_normal) - (radius * radius);

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
static double check_cylinder_caps(t_ray ray, t_cylinder *cylinder)
{
	double t;
	double closest_t = INFINITY;
	t_vect normalized_normal = ft_vect_norm(cylinder->norm);
	t_vect bottom_normal = ft_vect_mul_all(normalized_normal, -1);
	t_vect top_normal = normalized_normal;  // Already normalized

	t_plane bottom_cap = {
		.cord = ft_vect_add(cylinder->cord, ft_vect_mul_all(normalized_normal, -cylinder->height / 2)),
		.norm = bottom_normal,
		.radius = cylinder->diameter / 2.0
	};

	t_plane top_cap = {
		.cord = ft_vect_add(cylinder->cord, ft_vect_mul_all(normalized_normal, cylinder->height / 2)),
		.norm = top_normal,
		.radius = cylinder->diameter / 2.0
	};

	// Check bottom cap
	t = check_plane_collision(ray, &bottom_cap);
	if (t > 0.0)
		closest_t = t;

	// Check top cap
	t = check_plane_collision(ray, &top_cap);
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
double check_cylinder_collision(t_ray ray, t_cylinder *cylinder)
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
 * @param master Pointer to the master structure containing all scene objects
 * @return t_cylinder_collision Returns a structure containing the closest intersection
 *         parameter and pointer to the intersected cylinder
 * 
 * This function:
 * 1. Iterates through all cylinders in the scene
 * 2. Checks intersection with each cylinder
 * 3. Keeps track of the closest intersection found
 * 4. Returns both the intersection parameter and the intersected cylinder
 */
t_cylinder_collision find_closest_cylinder(t_ray ray, t_master *master)
{
	double					t;
	t_cylinder_collision	result;
	t_cylinder				*cylinder;

	result.closest_t = INFINITY;
	result.closest_cylinder = NULL;
	
	// Iterate through the linked list of cylinders to find the closest one
	cylinder = master->cylinder_head;
	while (cylinder)
	{
		t = check_cylinder_collision(ray, cylinder);
		if (t > 0.0 && t < result.closest_t)
		{
			result.closest_t = t;
			result.closest_cylinder = cylinder;
			if (t < EPSILON)
				break ;
		}
		cylinder = cylinder->next;
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
	rec->t = collision.closest_t;
	rec->point = ft_vect_add(ray.origin, ft_vect_mul_all(ray.direction, collision.closest_t));

	// First, determine if the hit point is on a cap or the cylindrical surface
	t_vect cp = ft_vect_sub(rec->point, collision.closest_cylinder->cord);
	t_vect normalized_normal = ft_vect_norm(collision.closest_cylinder->norm);
	double proj = ft_vect_dot(cp, normalized_normal);
	
	// Check if hit point is near either cap (using a small epsilon for floating-point comparison)
	double half_height = collision.closest_cylinder->height / 2.0;
	if (fabs(proj + half_height) < 1e-6)
	{
		// Hit is on bottom cap
		rec->normal = ft_vect_mul_all(normalized_normal, -1);
	}
	else if (fabs(proj - half_height) < 1e-6)
	{
		// Hit is on top cap
		rec->normal = normalized_normal;
	}
	else
	{
		// Hit is on cylindrical surface
		t_vect axis_point = ft_vect_add(collision.closest_cylinder->cord, 
			ft_vect_mul_all(normalized_normal, proj));
		rec->normal = ft_vect_norm(ft_vect_sub(rec->point, axis_point));
	}
}
