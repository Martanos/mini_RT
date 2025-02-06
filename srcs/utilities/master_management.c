/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:13:52 by malee             #+#    #+#             */
/*   Updated: 2025/02/06 20:16:19 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_free_img(t_master *master)
{
	if (!master)
		return ;
	printf("Destroying image\n");
	if (master->mlx_ptr && master->win_ptr)
	{
		mlx_destroy_window(master->mlx_ptr, master->win_ptr);
		master->win_ptr = NULL;
	}
	if (master->mlx_ptr && master->img.img_ptr)
	{
		mlx_destroy_image(master->mlx_ptr, master->img.img_ptr);
		master->img.img_ptr = NULL;
	}
	if (master->mlx_ptr)
	{
		mlx_destroy_display(master->mlx_ptr);
		free(master->mlx_ptr);
		master->mlx_ptr = NULL;
	}
}

void	ft_free_master(t_master *master)
{
	if (!master)
		return ;
	printf("Freeing master\n");
	printf("Freeing img\n");
	ft_free_img(master);
	printf("Freeing light\n");
	free_list(master->light_head, TYPE_LIGHT);
	printf("Freeing sphere\n");
	free_list(master->sphere_head, TYPE_SPHERE);
	printf("Freeing plane\n");
	free_list(master->plane_head, TYPE_PLANE);
	printf("Freeing cylinder\n");
	free_list(master->cylinder_head, TYPE_CYLINDER);
	printf("Freeing cone\n");
	free_list(master->cone_head, TYPE_CONE);
	free(master);
}
