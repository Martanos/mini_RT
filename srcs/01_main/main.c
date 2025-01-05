/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:13:57 by malee             #+#    #+#             */
/*   Updated: 2025/01/05 16:15:42 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_temp_object_creation(t_instruction_set **instruction_set)
{
	t_light_obj		*light_obj;
	t_plane_obj		*plane_obj;
	t_sphere_obj	*sphere_obj;
	t_cylinder_obj	*cylinder_obj;

	(*instruction_set)->amb_light_ratio = 0.5;
	(*instruction_set)->amb_light_rgb = WHITE;
	(*instruction_set)->camera_pos.x = 50.0;
	(*instruction_set)->camera_pos.y = 10.0;
	(*instruction_set)->camera_pos.z = 20.0;
	(*instruction_set)->camera_dir.x = 0.0;
	(*instruction_set)->camera_dir.y = 0.0;
	(*instruction_set)->camera_dir.z = 1.0;
	(*instruction_set)->camera_view_fov = 55.0;
	light_obj = (t_light_obj *)malloc(sizeof(t_light_obj));
	light_obj->light_pos.x = 0.0;
	light_obj->light_pos.y = 0.0;
	light_obj->light_pos.z = 0.0;
	light_obj->light_intensity = 0.0;
	light_obj->light_rgb = 0;
	(*instruction_set)->light_obj_list = &light_obj;
	plane_obj = (t_plane_obj *)malloc(sizeof(t_plane_obj));
	plane_obj->plane_pos.x = 0.0;
	plane_obj->plane_pos.y = -10.0;
	plane_obj->plane_pos.z = 0.0;
	plane_obj->plane_normal.x = 0.0;
	plane_obj->plane_normal.y = -1.0;
	plane_obj->plane_normal.z = 0.0;
	plane_obj->plane_rgb = RED;
	(*instruction_set)->plane_obj_list = &plane_obj;
	sphere_obj = (t_sphere_obj *)malloc(sizeof(t_sphere_obj));
	sphere_obj->sphere_pos.x = 0.0;
	sphere_obj->sphere_pos.y = 0.0;
	sphere_obj->sphere_pos.z = 0.0;
	sphere_obj->sphere_diameter = 0.0;
	sphere_obj->sphere_rgb = 0;
	(*instruction_set)->sphere_obj_list = &sphere_obj;
	cylinder_obj = (t_cylinder_obj *)malloc(sizeof(t_cylinder_obj));
	cylinder_obj->cylinder_pos.x = 0.0;
	cylinder_obj->cylinder_pos.y = 0.0;
	cylinder_obj->cylinder_pos.z = 0.0;
	cylinder_obj->cylinder_diameter = 0.0;
	cylinder_obj->cylinder_height = 0.0;
	cylinder_obj->cylinder_normal.x = 0.0;
	cylinder_obj->cylinder_normal.y = 0.0;
	cylinder_obj->cylinder_normal.z = 0.0;
	cylinder_obj->cylinder_rgb = 0;
	(*instruction_set)->cylinder_obj_list = &cylinder_obj;
}

int	main(int argc, char **argv)
{
	t_instruction_set	*instruction_set;
	(void)argv;
	instruction_set = (t_instruction_set *)malloc(sizeof(t_instruction_set));
	if (argc == 2)
	{
		ft_temp_object_creation(&instruction_set);
		ft_render_plane(instruction_set);
		// ft_render_scene(instruction_set);
	}
	else
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}
	return (0);
}
