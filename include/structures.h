/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:23:10 by malee             #+#    #+#             */
/*   Updated: 2025/01/10 21:45:01 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "mini_rt.h"

typedef struct	s_master;
typedef struct	s_amb;
typedef struct	s_cam;
typedef struct	s_light;
typedef struct	s_sphere;
typedef struct	s_plane;
typedef struct	s_cylinder;

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
	t_amb		*amb_head;
	t_cam		*cam_head;
	t_light		*light_head;
	t_sphere	*sphere_head;
	t_plane		*plane_head;
	t_cylinder	*cylinder_head;
}				t_master;

/*
** @brief Ambient light structure
** @param ratio ambient light ratio
** @param rgb ambient light rgb
*/
typedef struct s_amb
{
	double		ratio;
	uint32_t	rgb;
}				t_amb;

/*
** @brief Camera structure
** @param norm camera normal vector
** @param cord camera coordinate vector
** @param scal camera scale vector
** @param fov camera field of view
*/
typedef struct s_cam
{
	t_vect		norm;
	t_vect		cord;
	t_vect		scal;
	double		fov;
}				t_cam;

typedef struct s_light
{
	t_vect		norm;
	t_vect		cord;
	double		ratio;
	uint32_t	rgb;
	t_light		*next;
}				t_light;

typedef struct s_plane
{
	t_vect		norm;
	t_vect		cord;
	uint32_t	rgb;
	t_plane		*next;
}				t_plane;

typedef struct s_sphere
{
	t_vect		cord;
	double		diameter;
	uint32_t	rgb;
	t_sphere	*next;
}				t_sphere;

typedef struct s_cylinder
{
	t_vect		cord;
	t_vect		norm;
	double		diameter;
	double		height;
	uint32_t	rgb;
	t_cylinder	*next;
}				t_cylinder;

// Free functions
void			ft_free_master(t_master *master);
void			ft_free_light(t_light *light);
void			ft_free_plane(t_plane *plane);
void			ft_free_sphere(t_sphere *sphere);
void			ft_free_cylinder(t_cylinder *cylinder);

#endif
