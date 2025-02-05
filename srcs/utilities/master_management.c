/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:13:52 by malee             #+#    #+#             */
/*   Updated: 2025/02/05 20:32:34 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_free_img(t_master *master)
{
	printf("Destroying image\n");
	if (master->mlx_ptr && master->img.pixels_ptr)
		mlx_destroy_image(master->mlx_ptr, master->img.pixels_ptr);
}

void	ft_free_obj_pro(t_obj_pro *obj_pro)
{
	if (obj_pro->txm.texture_data)
		free(obj_pro->txm.texture_data);
	if (obj_pro->bpm.map)
		free(obj_pro->bpm.map);
	free(obj_pro);
}

void	ft_free_master(t_master *master)
{
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cyl;
	t_cone		*cone;

	printf("Freeing master\n");
	printf("Freeing img\n");
	// ft_free_img(master);
	printf("Freeing light\n");
	if (master->light_head)
	{
		light = master->light_head;
		ft_free_list_generic(light, ft_offsetof(light, light->next), 0);
	}
	printf("Freeing sphere\n");
	if (master->sphere_head)
	{
		sphere = master->sphere_head;
		ft_free_list_generic(sphere, ft_offsetof(sphere, sphere->next),
			ft_offsetof(sphere, &sphere->pro));
	}
	printf("Freeing plane\n");
	if (master->plane_head)
	{
		plane = master->plane_head;
		ft_free_list_generic(plane, ft_offsetof(plane, plane->next),
			ft_offsetof(plane, &plane->pro));
	}
	printf("Freeing cylinder\n");
	if (master->cylinder_head)
	{
		cyl = master->cylinder_head;
		ft_free_list_generic(cyl, ft_offsetof(cyl, cyl->next), ft_offsetof(cyl,
				&cyl->pro));
	}
	printf("Freeing cone\n");
	if (master->cone_head)
	{
		cone = master->cone_head;
		ft_free_list_generic(cone, ft_offsetof(cone, cone->next),
			ft_offsetof(cone, &cone->pro));
	}
}
