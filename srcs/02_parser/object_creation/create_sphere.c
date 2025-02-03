/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:32:13 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 20:39:30 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_add_sphere(t_master **master, t_sphere *sphere)
{
	t_sphere	*temp;

	temp = (*master)->sphere_head;
	if (!(*master)->sphere_head)
		(*master)->sphere_head = sphere;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = sphere;
	}
}

static bool	ft_check_extra_data(t_master **master, t_sphere **sphere,
		t_p_node **cur)
{
	while (*cur)
	{
		if (ft_strcmp((*cur)->str, "txm:") == 0)
		{
			if (!ft_add_sphere_texture(master, sphere, (*cur)->str + 4))
				return (false);
		}
		else if (ft_strcmp((*cur)->str, "bpm:") == 0)
		{
			if (!ft_add_sphere_bump_map(master, sphere, (*cur)->str + 4))
				return (false);
		}
		else if (ft_strcmp((*cur)->str, "mat:"))
		{
			if (!ft_add_sphere_material(sphere, (*cur)->str + 4))
				return (false);
		}
		else
			return (ft_format_error("Unknown sphere data"));
		(*cur) = (*cur)->next;
	}
	return (true);
}

// @brief Creates a sphere object
// @param master pointer to the master structure
// @param cur pointer to the current node in the parser node list
// @return true if successful, false if error
bool	ft_create_sphere(t_master **master, t_p_node **cur)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (false);
	(*cur) = (*cur)->next;
	sphere->cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector(sphere->cord, -INFINITY, INFINITY))
		return (free(sphere),
			ft_format_error("Sphere coordinates are not a valid vector"));
	(*cur) = (*cur)->next;
	sphere->diameter = ft_atod((*cur)->str);
	if (sphere->diameter <= 0)
		return (free(sphere),
			ft_format_error("Sphere diameter is not a positive number"));
	(*cur) = (*cur)->next;
	sphere->txm.pri_color = ft_get_rgb((*cur)->str);
	if (sphere->txm.pri_color < 0 || sphere->txm.pri_color > 0xFFFFFF)
		return (free(sphere),
			ft_format_error("Sphere color is out of range [0,255]"));
	(*cur) = (*cur)->next;
	if (*cur && !ft_check_extra_data(master, &sphere, cur))
		return (free(sphere), false);
	ft_add_sphere(master, sphere);
	return (true);
}
