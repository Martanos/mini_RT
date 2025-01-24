/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:23:10 by malee             #+#    #+#             */
/*   Updated: 2025/01/24 05:34:30 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "mini_rt.h"

typedef struct			s_master;
typedef struct			s_amb;
typedef struct			s_cam;
typedef struct			s_light;
typedef struct			s_sphere;
typedef struct			s_plane;
typedef struct			s_cylinder;
typedef struct			s_cone;
typedef struct			s_hit_record;

/*
** @brief Master structure contains pointers to all other structures mainly
** used for memory management
** @param amb pointer to the ambient light structure
** @param cam pointer to the camera structure
** @param l pointer to the light object structure
** @param sp_obj pointer to the sphere object structure
** @param pl_obj pointer to the plane object structure
** @param cy_obj pointer to the cylinder object structure
*/
typedef struct s_master
{
	t_amb				*amb_head;
	t_cam				*cam_head;
	t_light				*light_head;
	t_sphere			*sphere_head;
	t_plane				*plane_head;
	t_cylinder			*cylinder_head;
	t_cone				*cone_head;
}						t_master;

/*
** @brief Ambient light structure
** @param ratio ambient light ratio
** @param rgb ambient light rgb
*/
typedef struct s_amb
{
	double				ratio;
	uint32_t			rgb;
}						t_amb;

/*
** @brief Camera structure
** @param norm camera normal vector
** @param cord camera coordinate vector
** @param scal camera scale vector
** @param fov camera field of view
*/
typedef struct s_cam
{
	t_vect				norm;
	t_vect				cord;
	t_vect				scal;
	double				fov;
}						t_cam;

// OBJECTS
typedef struct s_light
{
	t_vect				norm;
	t_vect				cord;
	double				ratio;
	uint32_t			rgb;
	t_light				*next;
}						t_light;

typedef struct s_plane
{
	t_vect				norm;
	t_vect				cord;
	double				radius;
	uint32_t			rgb;
	t_plane				*next;
}						t_plane;

typedef struct s_sphere
{
	t_vect				cord;
	double				diameter;
	uint32_t			rgb;
	t_sphere			*next;
}						t_sphere;

typedef struct s_cylinder
{
	t_vect				cord;
	t_vect				norm;
	double				diameter;
	double				height;
	uint32_t			rgb;
	t_cylinder			*next;
}						t_cylinder;

typedef struct s_cone
{
	t_vect				cord;
	double				height;
	double				diameter;
	t_vect				norm;
	uint32_t			rgb;
	t_cone				*next;
}						t_cone;

// NOT SORTED
typedef struct s_ray
{
	t_vect				origin;
	t_vect				direction;
}						t_ray;

typedef struct s_hit_record
{
	t_vect				point;
	t_vect				normal;
	double				t;
}						t_hit_record;

typedef struct s_img
{
	void				*img_ptr;
	char				*pixels_ptr;
	int					bpp;
	int					endian;
	int					line_len;
}						t_img;

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				img;
	t_instruction_set	*instruction_set;
}						t_data;

typedef struct s_sphere_collision
{
	double				closest_t;
	t_sphere			*closest_sphere;
}						t_sphere_collision;

typedef struct s_plane_collision
{
	double				closest_t;
	t_plane				*closest_plane;
}						t_plane_collision;

typedef struct s_cylinder_collision
{
	double				closest_t;
	t_cylinder			*closest_cylinder;
}						t_cylinder_collision;

typedef struct s_cone_collision
{
	double				closest_t;
	t_cone				*closest_cone;
}						t_cone_collision;

// Memory management
void					ft_free_master(t_master *master);
void					ft_free_light(t_light *light);
void					ft_free_plane(t_plane *plane);
void					ft_free_sphere(t_sphere *sphere);
void					ft_free_cylinder(t_cylinder *cylinder);

#endif
