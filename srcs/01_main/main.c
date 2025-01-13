/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:13:57 by malee             #+#    #+#             */
/*   Updated: 2025/01/13 17:44:53 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_temp_object_creation(t_instruction_set **instruction_set)
{
	t_light_obj		**light_list;
	t_plane_obj		**plane_list;
	t_sphere_obj	**sphere_list;
	t_cylinder_obj	**cylinder_list;
	t_cone_object	**cone_list;

	// Initialize instruction set
	(*instruction_set)->amb_light_ratio = 0.5;
	(*instruction_set)->amb_light_rgb = WHITE;
	(*instruction_set)->camera_pos = vect_create(0.0, 0.0, -20.0);  // Move camera back
	(*instruction_set)->camera_dir = vect_normalize(vect_create(0.0, 0.0, 1.0));
	(*instruction_set)->camera_view_fov = 50.0;  // Wider FOV

	// Allocate lists (null-terminated arrays)
	light_list = malloc(2 * sizeof(t_light_obj *));
	plane_list = malloc(3 * sizeof(t_plane_obj *));
	sphere_list = malloc(2 * sizeof(t_sphere_obj *));
	cylinder_list = malloc(2 * sizeof(t_cylinder_obj *));
	cone_list = malloc(2 * sizeof(t_cone_object *));

	// Create light
	light_list[0] = malloc(sizeof(t_light_obj));
	light_list[0]->light_pos = vect_create(-5.0, 5.0, -10.0);
	light_list[0]->light_intensity = 1.0;
	light_list[0]->light_rgb = WHITE;
	// light_list[1] = malloc(sizeof(t_light_obj));
	// light_list[1]->light_pos = vect_create(5.0, 3.0, 5.0);
	// light_list[1]->light_intensity = 0.5;
	// light_list[1]->light_rgb = WHITE;
	light_list[1] = NULL;
	(*instruction_set)->light_obj_list = light_list;

	// Create plane
	plane_list[0] = malloc(sizeof(t_plane_obj));
	plane_list[0]->plane_pos = vect_create(0.0, -10.0, 0.0);
	plane_list[0]->plane_normal = vect_normalize(vect_create(0.0, 1.0, 0.0));
	plane_list[0]->plane_rgb = WHITE;
	// plane_list[1] = malloc(sizeof(t_plane_obj));
	// plane_list[1]->plane_pos = vect_create(0.0, 0.0, 200.0);
	// plane_list[1]->plane_normal = vect_normalize(vect_create(0.0, 0.0, 1.0));
	// plane_list[1]->plane_rgb = WHITE;
	plane_list[1] = malloc(sizeof(t_plane_obj));
	plane_list[1]->plane_pos = vect_create(5.0, 0.0, 0.0);
	plane_list[1]->plane_normal = vect_normalize(vect_create(-1.0, 0.0, 0.0));
	plane_list[1]->plane_rgb = WHITE;
	plane_list[2] = NULL;
	(*instruction_set)->plane_obj_list = plane_list;

	// Create sphere
	// sphere_list[0] = NULL;
	sphere_list[0] = malloc(sizeof(t_sphere_obj));
	sphere_list[0]->sphere_pos = vect_create(-3, 0.0, 3.0);  // 3 units in front of camera
	sphere_list[0]->sphere_diameter = 3.0;  // Larger sphere
	sphere_list[0]->sphere_rgb = WHITE;
	// sphere_list[1] = malloc(sizeof(t_sphere_obj));
	// sphere_list[1]->sphere_pos = vect_create(3.0, 2.0, 3.0);  // 2 units to the right of first sphere
	// sphere_list[1]->sphere_diameter = 2.5;  // Smaller sphere
	// sphere_list[1]->sphere_rgb = YELLOW;
	sphere_list[1] = NULL;
	(*instruction_set)->sphere_obj_list = sphere_list;

	// Create cylinder
	cylinder_list[0] = malloc(sizeof(t_cylinder_obj));
	cylinder_list[0]->cylinder_pos = vect_create(-6.0, -2.0, 2.0);
	cylinder_list[0]->cylinder_diameter = 3.0;
	cylinder_list[0]->cylinder_height = 3.0;
	cylinder_list[0]->cylinder_normal = vect_create(0.0, 0.0, 1.0);
	cylinder_list[0]->cylinder_rgb = ORANGE;
	// cylinder_list[1] = malloc(sizeof(t_cylinder_obj));
	// cylinder_list[1]->cylinder_pos = vect_create(1.0, -2.0, -10.0);
	// cylinder_list[1]->cylinder_diameter = 1.5;
	// cylinder_list[1]->cylinder_height = 2.0;
	// cylinder_list[1]->cylinder_normal = vect_create(0.0, 1.0, 1.0);
	// cylinder_list[1]->cylinder_rgb = ORANGE;
	cylinder_list[1] = NULL;
	(*instruction_set)->cylinder_obj_list = cylinder_list;

	// Create cone
	cone_list[0] = malloc(sizeof(t_cone_object));
	cone_list[0]->cone_pos = vect_create(-10.0, 0.0, 5.0);
	cone_list[0]->cone_height = 3.0;
	cone_list[0]->cone_diameter = 3.0;
	cone_list[0]->cone_normal = vect_create(1.0, 1.0, 1.0);
	cone_list[0]->cone_rgb = GREEN;
	cone_list[1] = NULL;
	(*instruction_set)->cone_obj_list = cone_list;
}

int	main(int argc, char **argv)
{
	t_instruction_set	*instruction_set;
	(void)argv;
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
