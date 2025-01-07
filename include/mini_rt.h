/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:49:00 by malee             #+#    #+#             */
/*   Updated: 2025/01/07 11:48:45 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "../libft/includes/libft.h"
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

// UTILS
void	ft_fatal(void);
void	ft_exit(t_instruction_set *instruction_set, char *error_message);

#endif
