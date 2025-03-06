/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:49:00 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 14:11:43 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "../libs/libft/includes/libft.h"
# include "../libs/librgb/includes/librgb.h"
# include "../libs/libvect/includes/libvect.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "object_structures.h"
# include "parser.h"
# include "renderer.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/param.h>
# include <time.h>
# include <unistd.h>

// DEFINES

# define WHITE "\033[37m"       // Full white
# define BLACK "\033[30m"       // Full black
# define RED "\033[31m"         // Bright red
# define GREEN "\033[32m"       // Bright green
# define BLUE "\033[34m"        // Bright blue
# define CYAN "\033[36m"        // Bright cyan
# define MAGENTA "\033[35m"     // Bright magenta
# define YELLOW "\033[33m"      // Bright yellow
# define ORANGE "\033[33m"      // Orange
# define PURPLE "\033[35m"      // Purple
# define GRAY "\033[37m"        // Gray
# define SEMI_RED "\033[31m"    // Semi-transparent red (alpha 50%)
# define SEMI_GREEN "\033[32m"  // Semi-transparent green (alpha 50%)
# define SEMI_BLUE "\033[34m"   // Semi-transparent blue (alpha 50%)
# define TRANSPARENT "\033[30m" // Fully transparent
# define RESET "\033[0m"

// MLX UTILS
void	keyhook_wrapper(t_scene **scene);
void	mousehook_wrapper(t_scene **scene);

// Scene management UTILS
void	ft_free_scene(t_scene *scene);
void	ft_free_img(t_scene *scene);

// Memory management UTILS
void	ft_free_node(t_obj_data *node, t_scene *scene);
void	ft_free_obj_list(t_obj_data *head, t_scene *scene);
void	ft_free_light_list(t_light *head);

// Error and warning utils
void	ft_exit(t_scene *scene, char *error_message);
bool	ft_error(char *msg);
void	ft_warning(char *msg);

#endif
