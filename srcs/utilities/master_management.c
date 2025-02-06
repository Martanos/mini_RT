/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:13:52 by malee             #+#    #+#             */
/*   Updated: 2025/02/06 15:34:19 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_free_img(t_master *master)
{
	printf("Destroying image\n");
	if (master->mlx_ptr && master->img.pixels_ptr)
		mlx_destroy_image(master->mlx_ptr, master->img.pixels_ptr);
}

void	ft_free_master(t_master *master)
{
	printf("Freeing master\n");
	printf("Freeing img\n");
	ft_free_img(master);
	printf("Freeing light\n");
}
