/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:25:29 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 13:34:34 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// @brief Graceful exit handles all expected memory leaks
// @param scene pointer to the scene structure
// @param error_message pointer to the error message
void	ft_exit(t_scene *scene, char *error_message)
{
	if (error_message)
	{
		ft_free_scene(scene);
		printf("Error\n");
		perror(error_message);
		exit(1);
	}
	ft_free_scene(scene);
	exit(0);
}

bool	ft_error(char *message)
{
	ft_putstr_fd(RED, 2);
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(message, 2);
	ft_putendl_fd(RESET, 2);
	return (false);
}
