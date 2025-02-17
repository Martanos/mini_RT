/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:14:23 by malee             #+#    #+#             */
/*   Updated: 2025/02/17 21:11:54 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_create_cam(t_master **master, t_p_node **cur)
{
	if ((*master)->cam_head.set)
		return (ft_error("Camera already exists"));
	else
		(*master)->cam_head.set = true;
	if (!ft_next(cur, "Camera has no coordinates"))
		return (false);
	(*master)->cam_head.cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*master)->cam_head.cord, -INFINITY, INFINITY,
			"Camera coordinates are out of range [-INFINITY, INFINITY]")
		|| !ft_next(cur, "Camera has no normal"))
		return (false);
	(*master)->cam_head.norm = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*master)->cam_head.norm, -1, 1,
			"Camera normal is out of range [-1, 1]") || !ft_next(cur,
			"Camera has no FOV"))
		return (false);
	(*master)->cam_head.fov = ft_atod((*cur)->str);
	if (!ft_inrange((*master)->cam_head.fov, 0, 180))
		return (ft_error("Camera FOV must be between 0 and 180"));
	(*cur) = (*cur)->next;
	if ((*cur) && (*cur)->str != NULL && (*cur)->str[0] != '\n')
		return (ft_error("Camera has extra data"));
	printf(GREEN "Camera created successfully\n" RESET);
	return (true);
}
