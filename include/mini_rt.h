/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:49:00 by malee             #+#    #+#             */
/*   Updated: 2025/02/28 22:27:53 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "../libs/libft/includes/libft.h"
# include "../libs/librgb/includes/librgb.h"
# include "../libs/libvect/includes/libvect.h"
# include "../minilibx-linux/mlx.h"
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
int		close_window(void *param);
int		key_hook(int keycode, void *param);

// Master management UTILS
void	ft_free_master(t_master *master);
void	ft_free_img(t_master *master);

// Memory management UTILS
void	ft_free_node(void *node, t_obj_type type, t_master *master);
void	ft_free_list(void *head, t_obj_type type, t_master *master);

// Error and warning utils
void	ft_exit(t_master *master, char *error_message);
bool	ft_error(char *msg);
void	ft_warning(char *msg);

#endif
