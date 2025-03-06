/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:14:23 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 14:47:02 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_create_cam(t_scene **scene, t_p_node **cur)
{
	if ((*scene)->cam_data.set)
		return (ft_error("Camera already exists"));
	else
		(*scene)->cam_data.set = true;
	if (!ft_next(cur, "Camera has no coordinates"))
		return (false);
	(*scene)->cam_data.cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*scene)->cam_data.cord, -INFINITY, INFINITY,
			"Camera coordinates are out of range [-INFINITY, INFINITY]")
		|| !ft_next(cur, "Camera has no normal"))
		return (false);
	(*scene)->cam_data.dir = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*scene)->cam_data.dir, -1, 1,
			"Camera normal is out of range [-1, 1]") || !ft_next(cur,
			"Camera has no FOV"))
		return (false);
	(*scene)->cam_data.fov = ft_atod((*cur)->str);
	if (!ft_inrange((*scene)->cam_data.fov, 0, 180))
		return (ft_error("Camera FOV must be between 0 and 180"));
	(*cur) = (*cur)->next;
	if ((*cur) && (*cur)->str != NULL && (*cur)->str[0] != '\n')
		return (ft_error("Camera has extra data"));
	printf(GREEN "Camera created successfully\n" RESET);
	return (true);
}
