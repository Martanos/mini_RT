/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:23:10 by malee             #+#    #+#             */
/*   Updated: 2025/01/05 14:27:48 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES
# define STRUCTURES

# include "mini_rt.h"

typedef struct		s_instruction_set;
typedef struct		s_light_obj;
typedef struct		s_sphere_obj;
typedef struct		s_plane_obj;
typedef struct		s_cylinder_obj;

typedef struct s_instruction_set
{
	double			amb_light_ratio;
	uint32_t		amb_light_rgb;
	double			camera_view_x;
	double			camera_view_y;
	double			camera_view_z;
	double			camera_view_normal_x;
	double			camera_view_normal_y;
	double			camera_view_normal_z;
	double			camera_view_fov;
	t_light_obj		**light_obj_list;
	t_sphere_obj	**sphere_obj_list;
	t_plane_obj		**plane_obj_list;
	t_cylinder_obj	**cylinder_obj_list;
}					t_instruction_set;

typedef struct s_light_obj
{
	double			light_x;
	double			light_y;
	double			light_z;
	double			light_intensity;
	uint32_t		light_rgb;
}					t_light_obj;

typedef struct s_plane_obj
{
	double			plane_x;
	double			plane_y;
	double			plane_z;
	double			plane_normal_x;
	double			plane_normal_y;
	double			plane_normal_z;
	uint32_t		plane_rgb;
}					t_plane_obj;

typedef struct s_sphere_obj
{
	double			sphere_x;
	double			sphere_y;
	double			sphere_z;
	double			sphere_diameter;
	uint32_t		sphere_rgb;
}					t_sphere_obj;

typedef struct s_cylinder_obj
{
	double			cylinder_x;
	double			cylinder_y;
	double			cylinder_z;
	double			cylinder_diameter;
	double			cylinder_height;
	double			cylinder_normal_x;
	double			cylinder_normal_y;
	double			cylinder_normal_z;
	uint32_t		cylinder_rgb;
}					t_cylinder_obj;

#endif
