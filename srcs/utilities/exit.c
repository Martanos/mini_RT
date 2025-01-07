/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:25:29 by malee             #+#    #+#             */
/*   Updated: 2025/01/07 11:49:18 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_free_instruction_set(t_instruction_set *instruction_set)
{
	while (instruction_set->light_obj_list)
	{
		free(instruction_set->light_obj_list);
		instruction_set->light_obj_list++;
	}
	while (instruction_set->sphere_obj_list)
	{
		free(instruction_set->sphere_obj_list);
		instruction_set->sphere_obj_list++;
	}
	while (instruction_set->plane_obj_list)
	{
		free(instruction_set->plane_obj_list);
		instruction_set->plane_obj_list++;
	}
	while (instruction_set->cylinder_obj_list)
	{
		free(instruction_set->cylinder_obj_list);
		instruction_set->cylinder_obj_list++;
	}
	free(instruction_set);
}

// TODO: Add memory management for mlx objects
// @brief Graceful exit handles all expected memory leaks
// @param instruction_set pointer to the instruction set
// @param error_message pointer to the error message
void	ft_exit(t_instruction_set *instruction_set, char *error_message)
{
	if (error_message)
	{
		ft_free_instruction_set(instruction_set);
		printf("Error\n");
		perror(error_message);
		exit(1);
	}
	ft_free_instruction_set(instruction_set);
	exit(0);
}
