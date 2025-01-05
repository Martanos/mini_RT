/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:06:36 by seayeo            #+#    #+#             */
/*   Updated: 2025/01/05 17:17:56 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PLANE_H
# define PLANE_H

# define WINDOW_WIDTH   800
# define WINDOW_HEIGHT  600

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				img;
	t_instruction_set	*instruction_set;
}	t_data;

# endif