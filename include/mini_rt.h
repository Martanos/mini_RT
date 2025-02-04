/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:49:00 by malee             #+#    #+#             */
/*   Updated: 2025/02/04 16:32:33 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "../libs/libft/includes/libft.h"
# include "../libs/librgb/includes/librgb.h"
# include "../libs/libvect/includes/libvect.h"
// # include "../minilibx-linux/mlx.h"
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

# define M_PI 3.14159265358979323846
# define DOUBLE_MAX 9007199254740991.0
# define DOUBLE_MIN -9007199254740991.0
# define BUFFER_SIZE 4096
# define WHITE 0xFFFFFFFF       // Full white
# define BLACK 0xFF000000       // Full black
# define RED 0xFFFF0000         // Bright red
# define GREEN 0xFF00FF00       // Bright green
# define BLUE 0xFF0000FF        // Bright blue
# define CYAN 0xFF00FFFF        // Bright cyan
# define MAGENTA 0xFFFF00FF     // Bright magenta
# define YELLOW 0xFFFFFF00      // Bright yellow
# define ORANGE 0xFFFFA500      // Orange
# define PURPLE 0xFF800080      // Purple
# define GRAY 0xFF808080        // Gray
# define SEMI_RED 0x80FF0000    // Semi-transparent red (alpha 50%)
# define SEMI_GREEN 0x8000FF00  // Semi-transparent green (alpha 50%)
# define SEMI_BLUE 0x800000FF   // Semi-transparent blue (alpha 50%)
# define TRANSPARENT 0x00000000 // Fully transparent
# define RESET "\033[0m"

// MLX UTILS
int		close_window(void *param);
int		key_hook(int keycode, void *param);

// Memory management
void	ft_free_master(t_master *master);
void	ft_free_img(t_master *master);

// UTILS
void	ft_fatal(char *msg);
void	ft_exit(t_master *master, char *error_message);
void	error_exit(char *error_message);

#endif
