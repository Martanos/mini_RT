/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_structures.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:32:45 by malee             #+#    #+#             */
/*   Updated: 2025/02/19 17:08:58 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_STRUCTURES_H
# define OBJECT_STRUCTURES_H

# include "mini_rt.h"

typedef struct s_master		t_master;
typedef struct s_amb		t_amb;
typedef struct s_cam		t_cam;
typedef struct s_light		t_light;
typedef struct s_sphere		t_sphere;
typedef struct s_plane		t_plane;
typedef struct s_cylinder	t_cylinder;
typedef struct s_cone		t_cone;
typedef struct s_material	t_material;
typedef struct s_texture	t_texture;
typedef struct s_bump_map	t_bump_map;
typedef struct s_obj_pro	t_obj_pro;

// OBJECT PROPERTIES

// Only for memory management
typedef enum e_obj_type
{
	TYPE_LIGHT,
	TYPE_SPHERE,
	TYPE_PLANE,
	TYPE_CYLINDER,
	TYPE_CONE
}							t_obj_type;

typedef enum e_texture_type
{
	SOLID_COLOR = 0,
	CHECKERED = 1,
	CUSTOM = 2
}							t_texture_type;

/*
** @brief Material properties for Phong reflection model
** @param ambient ambient reflection coefficient
** @param diffuse diffuse reflection coefficient
** @param specular specular reflection coefficient
** @param shininess controls the size of specular highlights
** @param reflection reflection coefficient for mirror-like surfaces
*/
typedef struct s_material
{
	bool					enabled;
	double amb;  // Range: [0.0, 1.0] - How much ambient light is reflected
	double diff; // Range: [0.0, 1.0] - How much diffuse light is reflected
	double spec; // Range: [0.0, 1.0] - How much specular light is reflected
	double shin; // Range: [0.0, ∞)   - Typically [1.0, 200.0] is common
					// Higher values = smaller, sharper highlights
	double refl; // Range: [0.0, 1.0] - How reflective the surface is
					// 0.0 = not reflective, 1.0 = perfect mirror
}							t_material;

/*
** @brief Texture properties for surface patterns
** @param type texture type (solid color, checkered, custom)
** @param scale scale factor for texture patterns
** @param primary_color primary color for patterns
** @param secondary_color secondary color for patterns
** @param texture_data pointer to custom texture data if needed
*/
typedef struct s_texture
{
	t_texture_type			type;
	double					scale;
	uint32_t				pri_color;
	uint32_t				sec_color;
	void					*img;
	int						width;
	int						height;
	int						*data;
	int						bpp;
	int						line_len;
	int						endian;
}							t_texture;

/*
** @brief Bump mapping properties
** @param enabled whether bump mapping is enabled
** @param map pointer to bump map data
*/
typedef struct s_bump_map
{
	bool					enabled;
	int						*data;
	int						bpp;
	int						line_len;
	int						endian;
	void					*img;
	int						width;
	int						height;
}							t_bump_map;

/*
** @brief Object properties structure
** @param mat material properties
** @param txm texture properties
** @param bpm bump map properties
*/
typedef struct s_obj_pro
{
	t_material				mat;
	t_texture				txm;
	t_bump_map				bpm;
}							t_obj_pro;

// OBJECT STRUCTURES

/*
** @brief Ambient light structure
** @param ratio ambient light ratio
** @param rgb ambient light rgb
*/
typedef struct s_amb
{
	double					ratio;
	uint32_t				rgb;
	bool					set;
}							t_amb;

/*
** @brief Camera structure
** @param norm camera normal vector
** @param cord camera coordinate vector
** @param scal camera scale vector
** @param fov camera field of view
*/
typedef struct s_cam
{
	t_vect					norm;
	t_vect					cord;
	double					fov;
	bool					set;
}							t_cam;

/*
** @brief Enhanced light structure for colored and multi-spot lights
** @param type light type (point, directional, spot)
** @param intensity light intensity factor
** @param color light color
** @param direction direction vector for spot lights
** @param angle cone angle for spot lights
*/
typedef struct s_light
{
	t_vect					cord;
	double					ratio;
	uint32_t				color;
	t_light					*next;
}							t_light;

/*
** @brief Plane structure
** @param norm plane normal vector
** @param cord plane coordinate vector
** @param radius plane radius
** @param pro object properties
** @param next pointer to the next plane object
*/
typedef struct s_plane
{
	t_vect					norm;
	t_vect					cord;
	double					radius;
	t_obj_pro				pro;
	t_plane					*next;
}							t_plane;

/*
** @brief Sphere structure
** @param cord sphere coordinate vector
** @param diameter sphere diameter
** @param pro object properties
** @param next pointer to the next sphere object
*/
typedef struct s_sphere
{
	t_vect					cord;
	double					diameter;
	t_obj_pro				pro;
	t_sphere				*next;
}							t_sphere;

/*
** @brief Cylinder structure
** @param cord cylinder coordinate vector
** @param norm cylinder normal vector
** @param diameter cylinder diameter
** @param height cylinder height
** @param pro object properties
** @param next pointer to the next cylinder object
*/
typedef struct s_cylinder
{
	t_vect					cord;
	t_vect					norm;
	double					diameter;
	double					height;
	t_obj_pro				pro;
	t_cylinder				*next;
}							t_cylinder;

/*
** @brief Cone structure
** @param cord cone coordinate vector
** @param norm cone normal vector
** @param height cone height
** @param diameter cone diameter
** @param pro object properties
** @param next pointer to the next cone object
*/
typedef struct s_cone
{
	t_vect					cord;
	t_vect					norm;
	double					height;
	double					diameter;
	t_obj_pro				pro;
	t_cone					*next;
}							t_cone;

// MLX OBJECTS

/*
** @brief Image structure
** @param img_ptr pointer to the image
** @param pixels_ptr pointer to the pixels
** @param bpp bits per pixel
** @param endian endianness
** @param line_len line length
*/
typedef struct s_img
{
	void					*img_ptr;
	char					*pixels_ptr;
	int						bpp;
	int						endian;
	int						line_len;
}							t_img;

// MASTER STRUCTURE
/*
** @brief Master structure contains pointers to all other structures mainly
** used for memory management
** @param amb_head pointer to the ambient light structure
** @param cam_head pointer to the camera structure
** @param light_head pointer to the light object structure
** @param sphere_head pointer to the sphere object structure
** @param plane_head pointer to the plane object structure
** @param cylinder_head pointer to the cylinder object structure
*/
typedef struct s_master
{
	void					*mlx_ptr;
	void					*win_ptr;
	t_img					img;
	t_amb					amb_head;
	t_cam					cam_head;
	t_light					*light_head;
	t_sphere				*sphere_head;
	t_plane					*plane_head;
	t_cylinder				*cylinder_head;
	t_cone					*cone_head;
	bool					aa_enabled;
}							t_master;

#endif
