/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:13:57 by malee             #+#    #+#             */
/*   Updated: 2025/01/05 14:31:48 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

void	ft_temp_object_creation(t_instruction_set **instruction_set)
{
	t_light_obj		*light_obj;
	t_plane_obj		*plane_obj;
	t_sphere_obj	*sphere_obj;
	t_cylinder_obj	*cylinder_obj;

	(*instruction_set)->amb_light_ratio = 0.0;
	(*instruction_set)->amb_light_rgb = 0;
	(*instruction_set)->camera_view_x = 0.0;
	(*instruction_set)->camera_view_y = 0.0;
	(*instruction_set)->camera_view_z = 0.0;
	(*instruction_set)->camera_view_normal_x = 0.0;
	(*instruction_set)->camera_view_normal_y = 0.0;
	(*instruction_set)->camera_view_normal_z = 0.0;
	(*instruction_set)->camera_view_fov = 0.0;
	light_obj = (t_light_obj *)malloc(sizeof(t_light_obj));
	light_obj->light_x = 0.0;
	light_obj->light_y = 0.0;
	light_obj->light_z = 0.0;
	light_obj->light_intensity = 0.0;
	light_obj->light_rgb = 0;
	(*instruction_set)->light_obj_list[0] = light_obj;
	plane_obj = (t_plane_obj *)malloc(sizeof(t_plane_obj));
	plane_obj->plane_x = 0.0;
	plane_obj->plane_y = 0.0;
	plane_obj->plane_z = 0.0;
	plane_obj->plane_normal_x = 0.0;
	plane_obj->plane_normal_y = 0.0;
	plane_obj->plane_normal_z = 0.0;
	plane_obj->plane_rgb = 0;
	(*instruction_set)->plane_obj_list[0] = plane_obj;
	sphere_obj = (t_sphere_obj *)malloc(sizeof(t_sphere_obj));
	sphere_obj->sphere_x = 0.0;
	sphere_obj->sphere_y = 0.0;
	sphere_obj->sphere_z = 0.0;
	sphere_obj->sphere_diameter = 0.0;
	sphere_obj->sphere_rgb = 0;
	(*instruction_set)->sphere_obj_list[0] = sphere_obj;
	cylinder_obj = (t_cylinder_obj *)malloc(sizeof(t_cylinder_obj));
	cylinder_obj->cylinder_x = 0.0;
	cylinder_obj->cylinder_y = 0.0;
	cylinder_obj->cylinder_z = 0.0;
	cylinder_obj->cylinder_diameter = 0.0;
	cylinder_obj->cylinder_height = 0.0;
	cylinder_obj->cylinder_normal_x = 0.0;
	cylinder_obj->cylinder_normal_y = 0.0;
	cylinder_obj->cylinder_normal_z = 0.0;
	cylinder_obj->cylinder_rgb = 0;
	(*instruction_set)->cylinder_obj_list[0] = cylinder_obj;
}

int	main(int argc, char **argv)
{
	t_instruction_set	*instruction_set;

	instruction_set = (t_instruction_set *)malloc(sizeof(t_instruction_set));
	if (argc == 2)
	{
		ft_temp_object_creation(&instruction_set);
		ft_render_scene(instruction_set);
	}
	else
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}
	return (0);
}
