/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:25:42 by malee             #+#    #+#             */
/*   Updated: 2025/03/04 16:33:49 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "mini_rt.h"
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

typedef struct s_hit_record			t_hit_record;
typedef struct s_ray				t_ray;
typedef struct s_img				t_img;
typedef struct s_sphere_collision	t_sphere_collision;
typedef struct s_plane_collision	t_plane_collision;
typedef struct s_cylinder_collision	t_cylinder_collision;
typedef struct s_intersection_info	t_intersection_info;

/*
 * Core Ray Tracing Structures:
 * These structures form the foundation of the ray tracing system,
	working together
 * to determine what objects are hit by rays and how they should be rendered.
 */

// Records information about where a ray intersects with an object
// - point: The exact point of intersection in 3D space
// - normal: Surface normal vector at the intersection point
// - t: Distance from ray origin to intersection point
typedef struct s_hit_record
{
	t_vect							point;
	t_vect							normal;
	double							t;
}									t_hit_record;

// Combines hit information with color data for the final pixel output
// - hit: Contains the intersection point, normal, and distance
// - color: The final calculated color for this intersection
typedef struct s_intersection_info
{
	t_hit_record					hit;
	uint32_t						color;
	t_obj_pro						properties;
}									t_intersection_info;

// Represents a ray in 3D space used for ray tracing
// - origin: Starting point of the ray
// - direction: Normalized vector indicating ray's direction
typedef struct s_ray
{
	t_vect							origin;
	t_vect							direction;
}									t_ray;

/*
 * Collision Tracking Structures:
 * Each geometric shape has its own collision
 * structure that follows the same pattern.
 * These structures store the closest
 * intersection found for that shape type during
 * ray tracing, allowing us to determine which object is visible at each pixel.
 */

// Tracks the closest sphere intersection
// - closest_t: Distance to the nearest sphere intersection
// - closest_sphere: Pointer to the sphere with the nearest intersection
typedef struct s_sphere_collision
{
	double							closest_t;
	t_sphere						*closest_sphere;
}									t_sphere_collision;

// Tracks the closest plane intersection
// - closest_t: Distance to the nearest plane intersection
// - closest_plane: Pointer to the plane with the nearest intersection
typedef struct s_plane_collision
{
	double							closest_t;
	t_plane							*closest_plane;
}									t_plane_collision;

// Tracks the closest cylinder intersection
// - closest_t: Distance to the nearest cylinder intersection
// - closest_cylinder: Pointer to the cylinder with the nearest intersection
typedef struct s_cylinder_collision
{
	double							closest_t;
	t_cylinder						*closest_cylinder;
}									t_cylinder_collision;

/*
 * Shape-Specific Intersection Functions:
 * Each geometric shape (sphere, plane,
 * cylinder) has three associated functions:
 * 1. find_closest_*: Finds the closest intersection
 * with any object of that type
 * 2. check_*_collision: Tests for intersection between
 * a ray and a single object
 * 3. calculate_*_hit: Computes intersection details (point,
 * normal) when a hit occurs
 */

// check_sphere.c
t_sphere_collision					find_closest_sphere(t_ray ray,
										t_master *master);
double								check_sphere_collision(t_ray ray,
										t_sphere *sphere);
void								calculate_sphere_hit(t_ray ray,
										t_sphere_collision collision,
										t_hit_record *rec);

// check_plane.c
double								check_capped_plane_collision(t_ray ray,
										t_plane plane);
t_plane_collision					find_closest_plane(t_ray ray,
										t_master *master);
double								check_plane_collision(t_ray ray,
										t_plane *plane);
void								calculate_plane_hit(t_ray ray,
										t_plane_collision collision,
										t_hit_record *rec);

// check_cylinder_main.c, check_cylinder_side.c, check_cylinder_caps.c,
// check_cylinder_utils.c
t_cylinder_collision				find_closest_cylinder(t_ray ray,
										t_master *master);
double								check_cylinder_collision(t_ray ray,
										t_cylinder *cylinder);
void								calculate_cylinder_hit(t_ray ray,
										t_cylinder_collision collision,
										t_hit_record *rec);
// Cylinder side surface functions
double								check_cylinder_side(t_ray ray,
										t_cylinder *cylinder);
// Cylinder cap functions
double								check_cylinder_caps(t_ray ray,
										t_cylinder *cylinder);
// Cylinder utility functions
t_vect								get_intersection_point(t_ray ray, double t);
double								check_cylinder_height(t_ray ray, double t,
										t_cylinder *cylinder);
t_vect								get_cylinder_normal(t_vect point,
										t_cylinder *cylinder, double proj);

// xpm_utils.c - XPM texture loading and application
void								apply_texture(t_texture texture, double u,
										double v, uint32_t *color);
void								checkerboard(double u, double v,
										t_texture txm, uint32_t *color);

/*
 * Intersection Management:
 * These functions handle the process of finding and tracking the closest
 * intersections between rays and scene objects. They work with the collision
 * structures to determine what's visible at each pixel.
 */

// intersection_check.c - Main intersection functions
bool								check_shadow_intersection(t_ray shadow_ray,
										double light_distance,
										t_master *master);
t_intersection_info					find_closest_intersection(t_ray ray,
										t_master *master);
t_ray								calculate_shadow_ray(t_vect hit_point,
										t_vect light_pos, t_vect normal);

// intersection_check_util.c - Intersection utility functions
void								update_closest_intersection(t_intersection_info *closest,
										t_intersection_info current);
void								check_sphere_intersection(t_ray ray,
										t_master *master,
										t_intersection_info *closest);
void								check_plane_intersection(t_ray ray,
										t_master *master,
										t_intersection_info *closest);
void								check_cylinder_intersection(t_ray ray,
										t_master *master,
										t_intersection_info *closest);

// texture_mapping.c - Texture mapping functions
void								get_sphere_uv(t_vect point, double *u,
										double *v);
void								get_plane_uv(t_vect point, t_plane *plane,
										double *u, double *v);

/*
 * Ray Tracing Core Functions:
 * These functions handle the main ray tracing logic,
	from determining background
 * colors to calculating final pixel colors based on ray intersections.
 */

// tracing.c - Core rendering functions
uint32_t							background_color(t_vect unit_direction);
uint32_t							ray_color(t_ray ray, t_master *master,
										int depth);
t_vect								calc_reflected_ray(t_vect incident,
										t_vect normal);
uint32_t							calc_specular(t_hit_record hit,
										t_vect cam_pos, t_light *light,
										t_material mat);
uint32_t							calculate_reflection(t_intersection_info info,
										t_ray ray, t_master *master, int depth);
uint32_t							calculate_diffuse_lighting(t_hit_record hit,
										t_light *light, uint32_t obj_color,
										t_material mat);
uint32_t							calculations(int x, int y,
										t_master *master);

void								my_pixel_put(t_img *img, int x, int y,
										int color);
void								ft_render_scene(t_master *master);
uint32_t							get_pixel(t_master *master, int x, int y);
void								put_pixel(t_master *master, int x, int y,
										uint32_t color);

#endif
