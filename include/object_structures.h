/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_structures.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:32:45 by malee             #+#    #+#             */
/*   Updated: 2025/03/04 19:12:33 by malee            ###   ########.fr       */
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
	double			amb;
	double			diff;
	double			spec;
	double			shin;
	double			refl;
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
	SPHERE = 0,
	PLANE = 1,
	CYLINDER = 2,
	CONE = 3
}					t_obj_type;

// Unique properties for each object type
typedef union u_obj_prop
{
	struct			s_plane
	{
		double		diameter;
		double		distance_from_origin;
	} t_plane;
	struct			s_sphere
	{
		double		diameter;
		double		radius;
		double		radius_squared;
	} t_sphere;
	struct			s_cylinder
	{
		double		height;
		double		diameter;
		double		radius;
		double		radius_squared;
		double		half_height;
		t_vect		top_cap;
		t_vect		bottom_cap;
	} t_cylinder;
	struct			s_cone
	{
		double		height;
		double		diameter;
		double		radius;
		double		radius_squared;
		double		half_height;
		double		slope;
		t_vect		apex;
		double		cos_apex;
	} t_cone;
}					t_obj_prop;

typedef struct s_local_coords
{
	t_vect			normal;
	t_vect			tangent;
	t_vect			bitangent;
}					t_local_coords;

typedef struct s_obj_data
{
	t_obj_type		type;
	t_vect			cord;
	t_vect			dir;
	t_material		mat;
	t_texture		txm;
	t_bump_map		bpm;
	t_local_coords	local;
	t_obj_prop		props;
	double			u;
	double			v;
	t_obj_data		*next;
}					t_obj_data;

typedef struct s_amb
{
	bool			set;
	double			ratio;
	uint32_t		rgb;
}					t_amb;

typedef struct s_cam
{
	bool			set;
	t_vect			cord;
	t_vect			dir;
	t_vect			up;
	t_vect			right;
	double			fov;
	double			aspect_ratio;
	int				win_height;
	int				win_width;
	double			viewport_height;
	double			viewport_width;
}					t_cam;

typedef struct s_light
{
	t_vect			cord;
	double			ratio;
	uint32_t		rgb;
	t_light			*next;
}					t_light;

typedef struct s_scene
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
	t_amb			amb_data;
	t_cam			cam_data;
	t_light			*light_data;
	t_obj_data		*obj_head;
	t_hit			*z_buffer;
	t_ray			*ray_buffer;
	bool			aa_enabled;
	int				aa_samples;
}					t_scene;

#endif
