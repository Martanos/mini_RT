/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:02:35 by malee             #+#    #+#             */
/*   Updated: 2025/02/04 16:07:00 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_free_img(t_master *master)
{
	mlx_destroy_image(master->mlx_ptr, master->img.img_ptr);
	free(master->img.img_ptr);
	free(master->img.pixels_ptr);
	free(master->img.bpp);
	free(master->img.endian);
	free(master->img.line_len);
}

void	ft_free_master(t_master *master)
{
	ft_free_img(master);
	free(master->light_head);
	free(master->sphere_head);
	free(master->plane_head);
	free(master->cylinder_head);
	free(master->cone_head);
}
