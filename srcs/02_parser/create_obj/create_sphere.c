/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:32:13 by malee             #+#    #+#             */
/*   Updated: 2025/02/17 21:11:45 by malee            ###   ########.fr       */
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

// @brief Creates a sphere object
// @param master pointer to the master structure
// @param cur pointer to the current node in the parser node list
// @return true if successful, false if error
static bool	ft_populate_sphere(t_master **master, t_sphere **sphere,
		t_p_node **cur)
{
	if (!ft_next(cur, "Sphere has no coordinates"))
		return (false);
	(*sphere)->cord = ft_get_xyz(cur);
	if (!ft_is_valid_vector((*sphere)->cord, -INFINITY, INFINITY,
			"Sphere coordinates are not a valid vector") || !ft_next(cur,
			"Sphere has no diameter"))
		return (false);
	(*sphere)->diameter = ft_atod((*cur)->str);
	if (!ft_inrange((*sphere)->diameter, 0, INFINITY))
		return (ft_error("Sphere diameter is not a positive number"));
	if (!ft_next(cur, "Sphere has no color"))
		return (false);
	if (!ft_get_rgb(&(*sphere)->pro.txm.pri_color, (*cur)->str))
		return (false);
	return (ft_extra_data(master, &((*sphere)->pro), cur));
}

bool	ft_create_sphere(t_master **master, t_p_node **cur)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (false);
	if (!ft_populate_sphere(master, &sphere, cur))
		return (free(sphere), false);
	ft_add_sphere(master, sphere);
	printf(GREEN "Sphere created successfully\n" RESET);
	return (true);
}
