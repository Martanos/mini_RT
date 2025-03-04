/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:25:42 by malee             #+#    #+#             */
/*   Updated: 2025/03/04 12:15:26 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "mini_rt.h"
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define MAX_DEPTH 50
# define EPSILON 1e-8
# define M_PI 3.14159265358979323846
# define DOUBLE_MAX 9007199254740991.0
# define DOUBLE_MIN -9007199254740991.0
# define BG_COLOR 0x000000
# define U_DEFAULT 0.0
# define V_DEFAULT 0.0

typedef struct s_hit
{
	double				t;
	t_vect				point;
	t_vect				normal;
	t_vect				tangent;
	t_vect				bitangent;
	t_obj_data			*object;
	bool				front_face;
}						t_hit;

typedef struct s_ray
{
	t_vect				origin;
	t_vect				direction;
	double				t_min;
	double				t_max;
	int					depth;
}						t_ray;

/*
 * Shape-Specific Intersection Functions:
 * Each geometric shape (sphere, plane,
 * cylinder, cone) has three associated functions:
 * 1. find_closest_*: Finds the closest intersection
 * with any object of that type
 * 2. check_*_collision: Tests for intersection between
 * a ray and a single object
 * 3. calculate_*_hit: Computes intersection details (point,
 * normal) when a hit occurs
 */

// check_sphere.c
t_sphere_collision		find_closest_sphere(t_ray ray, t_master *master);
double					check_sphere_collision(t_ray ray, t_sphere *sphere);
void					calculate_sphere_hit(t_ray ray,
							t_sphere_collision collision, t_hit_record *rec);

// check_plane.c
double					check_capped_plane_collision(t_ray ray, t_plane plane);
t_plane_collision		find_closest_plane(t_ray ray, t_master *master);
double					check_plane_collision(t_ray ray, t_plane *plane);
void					calculate_plane_hit(t_ray ray,
							t_plane_collision collision, t_hit_record *rec);

// check_cylinder.c
t_cylinder_collision	find_closest_cylinder(t_ray ray, t_master *master);
double					check_cylinder_collision(t_ray ray,
							t_cylinder *cylinder);
void					calculate_cylinder_hit(t_ray ray,
							t_cylinder_collision collision, t_hit_record *rec);

// check_cone.c
t_cone_collision		find_closest_cone(t_ray ray, t_master *master);
double					check_cone_collision(t_ray ray, t_cone *cone);
void					calculate_cone_hit(t_ray ray,
							t_cone_collision collision, t_hit_record *rec);

// xpm_utils.c - XPM texture loading and application
void					apply_texture(t_texture texture, double u, double v,
							uint32_t *color);
void					apply_tb(t_obj_pro pro, double u, double v,
							uint32_t *color);
void					checkerboard(double u, double v, t_texture txm,
							uint32_t *color);

/*
 * Intersection Management:
 * These functions handle the process of finding and tracking the closest
 * intersections between rays and scene objects. They work with the collision
 * structures to determine what's visible at each pixel.
 */

// intersection_check.c - Main intersection functions
bool					check_shadow_intersection(t_ray shadow_ray,
							double light_distance, t_master *master);
t_intersection_info		find_closest_intersection(t_ray ray, t_master *master);
t_ray					calculate_shadow_ray(t_vect hit_point, t_vect light_pos,
							t_vect normal);

// intersection_check_util.c - Intersection utility functions
void					update_closest_intersection(t_intersection_info *closest,
							t_intersection_info current);
void					check_sphere_intersection(t_ray ray, t_master *master,
							t_intersection_info *closest);
void					check_plane_intersection(t_ray ray, t_master *master,
							t_intersection_info *closest);
void					check_cylinder_intersection(t_ray ray, t_master *master,
							t_intersection_info *closest);
void					check_cone_intersection(t_ray ray, t_master *master,
							t_intersection_info *closest);

// texture_mapping.c - Texture mapping functions
void					get_sphere_uv(t_vect point, double *u, double *v);
void					get_plane_uv(t_vect point, t_plane *plane, double *u,
							double *v);

/*
 * Ray Tracing Core Functions:
 * These functions handle the main ray tracing logic,
	from determining background
 * colors to calculating final pixel colors based on ray intersections.
 */

// tracing.c - Core rendering functions
uint32_t				background_color(t_vect unit_direction);
uint32_t				ray_color(t_ray ray, t_master *master, int depth);
t_vect					calc_reflected_ray(t_vect incident, t_vect normal);
uint32_t				calc_specular(t_hit_record hit, t_vect cam_pos,
							t_light *light, t_material mat);
uint32_t				calculate_reflection(t_intersection_info info,
							t_ray ray, t_master *master, int depth);
uint32_t				calculate_diffuse_lighting(t_hit_record hit,
							t_light *light, uint32_t obj_color, t_material mat);
uint32_t				calculations(int x, int y, t_master *master);

void					my_pixel_put(t_img *img, int x, int y, int color);
void					apply_smaa(t_master *master);
void					ft_render_scene(t_master *master);
void					apply_post_aa(t_master *master);
uint32_t				get_pixel(t_master *master, int x, int y);
void					put_pixel(t_master *master, int x, int y,
							uint32_t color);

#endif
