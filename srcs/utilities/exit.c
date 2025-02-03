/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:25:29 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 15:17:54 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_free_master(t_master *master)
{
	t_light		*curr_light;
	t_light		*next_light;
	t_sphere	*curr_sphere;
	t_sphere	*next_sphere;
	t_plane		*curr_plane;
	t_plane		*next_plane;
	t_cylinder	*curr_cylinder;
	t_cylinder	*next_cylinder;
	t_cone		*curr_cone;
	t_cone		*next_cone;

	// Free ambient light
	if (master->amb_head)
		free(master->amb_head);

	// Free camera
	if (master->cam_head)
		free(master->cam_head);

	// Free light objects
	curr_light = master->light_head;
	while (curr_light)
	{
		next_light = curr_light->next;
		free(curr_light);
		curr_light = next_light;
	}

	// Free sphere objects
	curr_sphere = master->sphere_head;
	while (curr_sphere)
	{
		next_sphere = curr_sphere->next;
		free(curr_sphere);
		curr_sphere = next_sphere;
	}

	// Free plane objects
	curr_plane = master->plane_head;
	while (curr_plane)
	{
		next_plane = curr_plane->next;
		free(curr_plane);
		curr_plane = next_plane;
	}

	// Free cylinder objects
	curr_cylinder = master->cylinder_head;
	while (curr_cylinder)
	{
		next_cylinder = curr_cylinder->next;
		free(curr_cylinder);
		curr_cylinder = next_cylinder;
	}

	// Free cone objects
	curr_cone = master->cone_head;
	while (curr_cone)
	{
		next_cone = curr_cone->next;
		free(curr_cone);
		curr_cone = next_cone;
	}

	free(master);
}

// TODO: Add memory management for mlx objects
// @brief Graceful exit handles all expected memory leaks
// @param master pointer to the master structure
// @param error_message pointer to the error message
void	ft_exit(t_master *master, char *error_message)
{
	if (error_message)
	{
		ft_free_master(master);
		printf("Error\n");
		perror(error_message);
		exit(1);
	}
	ft_free_master(master);
	exit(0);
}
