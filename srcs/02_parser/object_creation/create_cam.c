/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:14:23 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 17:45:07 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_create_cam(t_master **master, t_p_node **cur)
{
	if ((*master)->cam_head.set)
		return (ft_format_error("Camera already exists"));
	else
		(*master)->cam_head.set = true;
	(*cur) = (*cur)->next;
	(*master)->cam_head.norm = ft_get_xyz(cur);
	if (isnan((*master)->cam_head.norm.x) || isnan((*master)->cam_head.norm.y)
		|| isnan((*master)->cam_head.norm.z))
		return (ft_format_error("Camera normal is not a valid vector"));
	(*cur) = (*cur)->next;
	(*master)->cam_head.cord = ft_get_xyz(cur);
	if (!ft_inrange((*master)->cam_head.cord.x, -1, 1)
		|| !ft_inrange((*master)->cam_head.cord.y, -1, 1)
		|| !ft_inrange((*master)->cam_head.cord.z, -1, 1))
		return (ft_format_error("Camera coordinates are out of range [-1, 1]"));
	(*cur) = (*cur)->next;
	(*master)->cam_head.fov = ft_atod(cur);
	if (!ft_inrange((*master)->cam_head.fov, 0, 180))
		return (ft_format_error("Camera FOV must be between 0 and 180"));
	(*cur) = (*cur)->next;
	if (*cur)
		return (ft_format_error("Camera has extra data"));
	return (false);
}
