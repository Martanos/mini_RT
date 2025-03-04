/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:59:59 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/04 14:45:11 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

int	close_window(void *param)
{
	t_master	*master;

	master = (t_master *)param;
	ft_free_master(master);
	exit(0);
	return (0);
}

// Handle keypress event
int	key_hook(int keycode, void *param)
{
	t_master	*master;

	master = (t_master *)param;
	if (keycode == 65307)
	{
		ft_free_master(master);
		exit(0);
	}
	else if (keycode == 97)
	{
		master->aa_enabled = !master->aa_enabled;
		printf("Anti-aliasing: %s\n", master->aa_enabled ? "ON" : "OFF");
		ft_render_scene(master);
	}
	return (0);
}
