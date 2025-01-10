/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:49:00 by malee             #+#    #+#             */
/*   Updated: 2025/01/10 17:48:40 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "../libs/libft/includes/libft.h"
# include "../libs/librgb/includes/librgb.h"
# include "../libs/libvect/includes/libvect.h"
# include "parser.h"
# include "structures.h"
# include "utilities.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
//# include <mlx.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/param.h>
# include <unistd.h>

# define BUFFER_SIZE 4096

# define RED "\033[31m"
# define ORANGE "\033[38;5;208m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define RESET "\033[0m"

// UTILS
void	ft_fatal(char *msg);
void	ft_exit(t_master *master, char *error_message);
#endif
