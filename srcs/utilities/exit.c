/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:25:29 by malee             #+#    #+#             */
/*   Updated: 2025/02/04 16:06:27 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
