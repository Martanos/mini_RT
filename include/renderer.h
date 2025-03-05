/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:25:42 by malee             #+#    #+#             */
/*   Updated: 2025/03/05 21:11:26 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "mini_rt.h"
# define AA 4
# define DEFAULT_WINDOW_WIDTH 800
# define DEFAULT_WINDOW_HEIGHT 600
# define MAX_RECURSION_DEPTH 30
# define EPSILON 1e-8
# define M_PI 3.14159265358979323846
# define DOUBLE_MAX 9007199254740991.0
# define DOUBLE_MIN -9007199254740991.0
# define U_DEFAULT 0.0
# define V_DEFAULT 0.0

typedef struct s_hit
{
	double		t;
	double		u;
	double		v;
	int			img_x;
	int			img_y;
	t_vect		point;
	t_vect		normal;
	t_vect		tangent;
	t_vect		bitangent;
	t_vect		pixel_color;
	uint32_t	final_color;
	t_obj_data	*object;
	bool		front_face;
}				t_hit;

typedef struct s_ray
{
	t_vect		origin;
	t_vect		direction;
	double		u;
	double		v;
	double		u_offset;
	double		v_offset;
	double		t_min;
	double		t_max;
	int			depth;
}				t_ray;

typedef struct s_z_buffer
{
	t_hit		hit;
	t_ray		ray;
	t_hit		shadow_hit;
	t_ray		shadow_ray;
	t_hit		reflect_hit;
	t_ray		reflect_ray;
	t_vect		reflect_color;
}				t_z_buffer;

typedef struct s_quadratic
{
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t;
	double		t1;
	double		t2;
}				t_quadratic;

// MLX UTILS
void			ft_pixel_put(t_img *img, int x, int y, int color);
// 0. Static value setup
bool			ft_obj_prep_main(t_scene **scene);
void			ft_setup_obj_calcs(t_scene **scene);
void			ft_setup_sphere(t_obj_data **obj);
void			ft_setup_plane(t_obj_data **obj);
void			ft_setup_cylinder(t_obj_data **obj);
void			ft_setup_cone(t_obj_data **obj);
// 1. Ray setup
void			ft_setup_ray(t_scene **scene);
// 2. hit calcs
bool			ft_intersect_main(t_scene **scene);
bool			ft_intersect_sphere(t_scene **scene, t_obj_data *sphere);
bool			ft_intersect_plane(t_scene **scene, t_obj_data *plane);
bool			ft_intersect_cylinder(t_scene **scene, t_obj_data *cylinder);
bool			ft_intersect_cylinder_side(t_ray *ray, t_obj_data *cylinder,
					t_quadratic *quad, t_hit *hit);
bool			ft_intersect_cylinder_cap(t_ray *ray, t_obj_data *cylinder,
					t_hit *hit, bool is_top_cap);
bool			ft_intersect_cone(t_scene **scene, t_obj_data *cone);
bool			ft_intersect_cone_side(t_ray *ray, t_obj_data *cone,
					t_quadratic *quad, t_hit *hit);
bool			ft_intersect_cone_base(t_ray *ray, t_obj_data *cone,
					t_hit *hit);
// 3. Colour calcs
void			ft_get_base_colour(t_hit **hit);
// 4. Normal calcs
void			ft_apply_bump_mapping(t_hit **hit);
void			ft_calculate_surface_normal(t_hit **hit);
// 5. Lighting calcs
void			ft_apply_lighting(t_scene **scene, t_ray *ray, t_hit *hit,
					t_vect *color);
void			ft_calculate_lighting(t_scene **scene, t_ray *ray, t_hit *hit);
bool			ft_is_in_shadow(t_scene **scene, t_light *light);
t_vect			ft_calculate_specular(t_ray *ray, t_hit *hit, t_light *light,
					t_vect light_dir);

#endif
