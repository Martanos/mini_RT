/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:23:10 by malee             #+#    #+#             */
/*   Updated: 2025/01/13 13:33:22 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES
# define STRUCTURES

# include <stdint.h>
// # include "mini_rt.h"
typedef struct 		s_vect t_vect;
typedef struct		s_instruction_set t_instruction_set;
typedef struct		s_light_obj t_light_obj;
typedef struct		s_sphere_obj t_sphere_obj;
typedef struct		s_plane_obj t_plane_obj;
typedef struct		s_cylinder_obj t_cylinder_obj;
typedef struct		s_hit_record t_hit_record;

typedef struct s_vect
{
	double	x;
	double	y;
	double	z;
}	t_vect;

typedef struct s_ray
{
	t_vect	origin;
	t_vect	direction;
}	t_ray;

typedef struct s_instruction_set
{
	double			amb_light_ratio;
	uint32_t		amb_light_rgb;
	t_vect			camera_pos;
	t_vect 			camera_dir;
	double			camera_view_fov;
	t_light_obj		**light_obj_list;
	t_sphere_obj	**sphere_obj_list;
	t_plane_obj		**plane_obj_list;
	t_cylinder_obj	**cylinder_obj_list;
}					t_instruction_set;

typedef struct s_light_obj
{
	t_vect			light_pos;
	double			light_intensity;
	uint32_t		light_rgb;
}					t_light_obj;

typedef struct s_plane_obj
{
	t_vect			plane_pos;
	t_vect			plane_normal;
	uint32_t		plane_rgb;
}					t_plane_obj;

typedef struct s_sphere_obj
{
	t_vect 			sphere_pos;
	double			sphere_diameter;
	uint32_t		sphere_rgb;
}					t_sphere_obj;

typedef struct s_capped_plane
{
    t_vect      position;
    t_vect      normal;
    double      radius;
} t_capped_plane;

typedef struct s_cylinder_obj
{
	t_vect			cylinder_pos;
	double			cylinder_diameter;
	double			cylinder_height;
	t_vect			cylinder_normal;
	uint32_t		cylinder_rgb;
}					t_cylinder_obj;

typedef struct s_hit_record
{
	t_vect			point;
	t_vect			normal;
	double			t;
}					t_hit_record;

#endif
