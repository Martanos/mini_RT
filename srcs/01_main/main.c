/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:13:57 by malee             #+#    #+#             */
/*   Updated: 2025/01/07 12:59:16 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_temp_object_creation(t_instruction_set **instruction_set)
{
	t_light_obj		**light_list;
	t_plane_obj		**plane_list;
	t_sphere_obj	**sphere_list;
	t_cylinder_obj	**cylinder_list;

	// Initialize instruction set
	(*instruction_set)->amb_light_ratio = 0.5;
	(*instruction_set)->amb_light_rgb = WHITE;
	(*instruction_set)->camera_pos = vect_create(0.0, 0.0, -5.0);  // Move camera back
	(*instruction_set)->camera_dir = vect_normalize(vect_create(0.0, 0.0, 1.0));
	(*instruction_set)->camera_view_fov = 90.0;  // Wider FOV

	// Allocate lists (null-terminated arrays)
	light_list = malloc(2 * sizeof(t_light_obj *));  // Space for 1 light + NULL
	plane_list = malloc(2 * sizeof(t_plane_obj *));  // Space for 1 plane + NULL
	sphere_list = malloc(2 * sizeof(t_sphere_obj *));  // Space for 1 sphere + NULL
	cylinder_list = malloc(2 * sizeof(t_cylinder_obj *));  // Space for 1 cylinder + NULL

	// Create light
	light_list[0] = malloc(sizeof(t_light_obj));
	light_list[0]->light_pos = vect_create(-5.0, 5.0, -5.0);
	light_list[0]->light_intensity = 0.7;
	light_list[0]->light_rgb = WHITE;
	light_list[1] = NULL;
	(*instruction_set)->light_obj_list = light_list;

	// Create plane
	plane_list[0] = malloc(sizeof(t_plane_obj));
	plane_list[0]->plane_pos = vect_create(0.0, -2.0, 0.0);
	plane_list[0]->plane_normal = vect_normalize(vect_create(0.0, 1.0, 0.0));
	plane_list[0]->plane_rgb = RED;
	plane_list[1] = NULL;
	(*instruction_set)->plane_obj_list = plane_list;

	// Create sphere
	sphere_list[0] = malloc(sizeof(t_sphere_obj));
	sphere_list[0]->sphere_pos = vect_create(0.0, 0.0, 3.0);  // 3 units in front of camera
	sphere_list[0]->sphere_diameter = 2.0;  // Larger sphere
	sphere_list[0]->sphere_rgb = GREEN;
	sphere_list[1] = NULL;
	(*instruction_set)->sphere_obj_list = sphere_list;

	// Create cylinder
	cylinder_list[0] = malloc(sizeof(t_cylinder_obj));
	cylinder_list[0]->cylinder_pos = vect_create(0.0, 0.0, 0.0);
	cylinder_list[0]->cylinder_diameter = 0.0;
	cylinder_list[0]->cylinder_height = 0.0;
	cylinder_list[0]->cylinder_normal = vect_create(0.0, 1.0, 0.0);
	cylinder_list[0]->cylinder_rgb = BLUE;
	cylinder_list[1] = NULL;
	(*instruction_set)->cylinder_obj_list = cylinder_list;
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
