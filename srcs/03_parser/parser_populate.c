/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_populate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:30:00 by malee             #+#    #+#             */
/*   Updated: 2025/02/12 17:21:09 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	ft_identify(t_master **master, t_p_node **cur)
{
	printf(GREEN "Identifying: %s\n" RESET, (*cur)->str);
	if (ft_strcmp((*cur)->str, "A") == 0)
		return (ft_create_amb(master, cur));
	else if (ft_strcmp((*cur)->str, "C") == 0)
		return (ft_create_cam(master, cur));
	else if (ft_strcmp((*cur)->str, "L") == 0)
		return (ft_create_light(master, cur));
	else if (ft_strcmp((*cur)->str, "pl") == 0)
		return (ft_create_plane(master, cur));
	else if (ft_strcmp((*cur)->str, "cy") == 0)
		return (ft_create_cylinder(master, cur));
	else if (ft_strcmp((*cur)->str, "sp") == 0)
		return (ft_create_sphere(master, cur));
	else if (ft_strcmp((*cur)->str, "co") == 0)
		return (ft_create_cone(master, cur));
	return (ft_format_error("Invalid identifier"));
}

// todo: move to parser
static bool	ft_initmlx(t_master **master)
{
	(*master)->mlx_ptr = mlx_init();
	if (!(*master)->mlx_ptr)
		return (ft_format_error("mlx failed to initialize"));
	(*master)->win_ptr = mlx_new_window((*master)->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "miniRT");
	if (!(*master)->win_ptr)
		return (ft_format_error("mlx failed to create window"));
	(*master)->img.img_ptr = mlx_new_image((*master)->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	if (!(*master)->img.img_ptr)
		return (ft_format_error("mlx failed to create image"));
	(*master)->img.pixels_ptr = mlx_get_data_addr((*master)->img.img_ptr,
			&(*master)->img.bpp, &(*master)->img.line_len,
			&(*master)->img.endian);
	if (!(*master)->img.pixels_ptr)
		return (ft_format_error("mlx failed to get image address"));
	return (true);
}

/*
** @brief Returns a master structure with the parsed data
** @param head pointer to the head of the parser node list
** @return false if successful, true if error
*/
t_master	*ft_populate(t_p_node *cur)
{
	t_master	*master;

	master = (t_master *)ft_calloc(1, sizeof(t_master));
	if (!master)
		return (NULL);
	if (!ft_initmlx(&master))
		return (ft_free_master(master), NULL);
	while (cur)
	{
		if (!ft_identify(&master, &cur))
			return (ft_free_master(master), NULL);
		while (cur && cur->str && ft_isspace(cur->str[0]))
			cur = cur->next;
	}
	return (master);
}
