/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_tracking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:08:11 by seayeo            #+#    #+#             */
/*   Updated: 2025/03/06 14:54:29 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_rt.h"

// Mouse release event handler
static int	mouse_release(int button, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (button == 1)
		scene->mouse_data.dragging = 0;
	return (0);
}

// Mouse press event handler
static int	mouse_press(int button, int x, int y, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	// Check if the mouse is near the bottom-right corner (for resizing)
	if (button == 1 && x >= (scene->cam_data.win_width - 10)
		&& y >= (scene->cam_data.win_height - 10))
	{
		scene->mouse_data.dragging = 1;
		scene->mouse_data.start_x = x;
		scene->mouse_data.start_y = y;
	}
	return (0);
}

// Mouse motion event handler
// Calculate how far the mouse has moved
// Update the width and height based on mouse movement
// Enforce minimum window size
// Resize the window based on new width and height
// Update the starting mouse position for the next movement
static int	mouse_move(int x, int y, void *param)
{
	t_scene	*scene;
	int		delta_x;
	int		delta_y;

	scene = (t_scene *)param;
	if (scene->mouse_data.dragging)
	{
		delta_x = x - scene->mouse_data.start_x;
		delta_y = y - scene->mouse_data.start_y;
		scene->cam_data.win_width += delta_x;
		scene->cam_data.win_height += delta_y;
		if (scene->cam_data.win_width < MIN_WIDTH)
			scene->cam_data.win_width = MIN_WIDTH;
		if (scene->cam_data.win_height < MIN_HEIGHT)
			scene->cam_data.win_height = MIN_HEIGHT;
		scene->mouse_data.start_x = x;
		scene->mouse_data.start_y = y;
	}
	return (0);
}

// Wrapper function to set up all mouse hooks
// mask tells mlx_hook which events to listen for
// event code passes the event to the appropriate handler
// 1L << 6 is the mask for mouse movement events
// 1L << 3 is the mask for mouse release events

void	mousehook_wrapper(t_scene **scene)
{
	mlx_mouse_hook((*scene)->win_ptr, mouse_press, *scene);
	mlx_hook((*scene)->win_ptr, 6, 1L << 6, mouse_move, *scene);
	mlx_hook((*scene)->win_ptr, 5, 1L << 3, mouse_release, *scene);
}
