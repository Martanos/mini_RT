/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   librgb.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:17:18 by malee             #+#    #+#             */
/*   Updated: 2025/02/04 15:35:04 by seayeo           ###   ########.fr       */
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
void	    ft_convert_rgb_arr(uint32_t rgb, uint8_t *rgb_arr);
void        ft_clamp_rgb_values(double *final, uint8_t *rgb_arr);

#endif
