/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   librgb.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:17:18 by malee             #+#    #+#             */
/*   Updated: 2025/02/23 00:51:32 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRGB_H
# define LIBRGB_H

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
void		ft_convert_rgb_arr(uint32_t rgb, uint8_t *rgb_arr);
void		ft_clamp_rgb_values(uint8_t *final, uint8_t *rgb_arr);
void		ft_color_mixer(uint8_t *rgb_arr1, uint8_t *rgb_arr2, double ratio);
void		ft_color_to_rgb(uint32_t color, double *r, double *g, double *b);
uint32_t	ft_rgb_to_color(double r, double g, double b);
uint32_t	ft_color_multiply(uint32_t c1, uint32_t c2);
uint32_t	ft_color_scale(uint32_t color, double t);

#endif
