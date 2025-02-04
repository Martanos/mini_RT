/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   librgb.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:17:18 by malee             #+#    #+#             */
/*   Updated: 2025/02/04 14:38:55 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRGB_H
# define LIBRGB_H

# include "mini_rt.h"
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

uint32_t	ft_get_b(uint32_t rgb);
uint32_t	ft_get_g(uint32_t rgb);
uint32_t	ft_get_r(uint32_t rgb);
uint32_t	ft_create_rgb(uint8_t r, uint8_t g, uint8_t b);

#endif
