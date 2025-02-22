/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_structures.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:32:45 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 22:05:21 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_STRUCTURES_H
# define OBJECT_STRUCTURES_H

# include "mini_rt.h"

// MLX OBJECTS
typedef struct s_img
{
	void			*img_ptr;
	char			*pixels_ptr;
	int				bpp;
	int				endian;
	int				line_len;
}					t_img;

typedef enum e_texture_type
{
	SOLID_COLOR = 0,
	CHECKERED = 1,
	CUSTOM = 2
}					t_texture_type;

typedef struct s_texture
{
	t_texture_type	type;
	double			scale;
	uint32_t		pri_color;
	uint32_t		sec_color;
	void			*img;
	int				width;
	int				height;
	int				*data;
	int				bpp;
	int				line_len;
	int				endian;
}					t_texture;

// Extra object properties
typedef struct s_material
{
	bool			enabled;
	double amb;  // Range: [0.0, 1.0] - How much ambient light is reflected
	double diff; // Range: [0.0, 1.0] - How much diffuse light is reflected
	double spec; // Range: [0.0, 1.0] - How much specular light is reflected
	double shin; // Range: [0.0, ∞)   - Typically [1.0, 200.0] is common
					// Higher values = smaller, sharper highlights
	double refl; // Range: [0.0, 1.0] - How reflective the surface is
					// 0.0 = not reflective, 1.0 = perfect mirror
}					t_material;

typedef struct s_bump_map
{
	bool			enabled;
	int				*data;
	int				bpp;
	int				line_len;
	int				endian;
	void			*img;
	int				width;
	int				height;
}					t_bump_map;

typedef enum e_obj_type
{
	LIGHT = 0,
	SPHERE = 1,
	PLANE = 2,
	CYLINDER = 3,
	CONE = 4
}					t_obj_type;

// Unique properties for each object type
typedef union u_obj_prop
{
	struct
	{
		double		ratio;
	} light;
	struct
	{
		double		diameter;
	} plane;
	struct
	{
		double		diameter;
	} sphere;
	struct
	{
		double		height;
		double		diameter;
	} cylinder;
	struct
	{
		double		height;
		double		diameter;
	} cone;
}					t_obj_prop;

typedef struct s_obj_data
{
	t_obj_type		type;
	t_vect			cord;
	t_vect			dir;
	t_material		mat;
	t_texture		txm;
	t_bump_map		bpm;
	t_obj_prop		props;
	t_obj_data		*next;
}					t_obj_data;

typedef struct s_amb
{
	double			ratio;
	uint32_t		rgb;
	bool			set;
}					t_amb;

typedef struct s_cam
{
	t_vect			norm;
	t_vect			cord;
	double			fov;
	bool			set;
}					t_cam;

typedef struct s_scene
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
	t_amb			*amb_data;
	t_cam			*cam_data;
	t_obj_data		*obj_data;
	bool			aa_enabled;
}					t_scene;

#endif
