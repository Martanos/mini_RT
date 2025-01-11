/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:49:00 by malee             #+#    #+#             */
/*   Updated: 2025/01/11 17:22:24 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT
# define MINI_RT

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "../minilibx-linux/mlx.h"
# include "structures.h"
# include "../srcs/renderplane/plane.h"

#define WHITE       0xFFFFFFFF   // Full white
#define BLACK       0xFF000000   // Full black
#define RED         0xFFFF0000   // Bright red
#define GREEN       0xFF00FF00   // Bright green
#define BLUE        0xFF0000FF   // Bright blue
#define CYAN        0xFF00FFFF   // Bright cyan
#define MAGENTA     0xFFFF00FF   // Bright magenta
#define YELLOW      0xFFFFFF00   // Bright yellow
#define ORANGE      0xFFFFA500   // Orange
#define PURPLE      0xFF800080   // Purple
#define GRAY        0xFF808080   // Gray
#define SEMI_RED    0x80FF0000   // Semi-transparent red (alpha 50%)
#define SEMI_GREEN  0x8000FF00   // Semi-transparent green (alpha 50%)
#define SEMI_BLUE   0x800000FF   // Semi-transparent blue (alpha 50%)
#define TRANSPARENT 0x00000000   // Fully transparent


// RENDERPLANE

void			ft_render_scene(t_instruction_set *instruction_set);
// UTILS

// vector_utils.c
t_vect	vect_add(t_vect v1, t_vect v2);
t_vect	vect_sub(t_vect v1, t_vect v2);
double	vect_magnitude(t_vect v);
double	vect_dot(t_vect v1, t_vect v2);
t_vect	vect_normalize(t_vect v);
t_vect	vect_divide(t_vect v1, double n);
t_vect  vect_create(double x, double y, double z);
t_vect	vect_multiply(t_vect v1, double n);
t_vect	vect_cross(t_vect v1, t_vect v2);
t_vect	ft_vect_mul_all(t_vect a, double scalar);
void	set_face_normal(t_hit_record *rec, const t_ray *r, const t_vect *outward_normal);

// misc.c
void	error_exit(char *error_message);
void	my_pixel_put(t_img *img, int x, int y, int color);
int		close_window(void *param);
int		key_hook(int keycode, void *param);

#endif
