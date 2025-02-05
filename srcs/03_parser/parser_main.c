/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:22:29 by malee             #+#    #+#             */
/*   Updated: 2025/02/05 19:47:39 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
** @brief Facilitates the parsing of the file
** @param file_path path to the file
** @return pointer to the master structure
*/
t_master	*ft_parser(char *file_path)
{
	t_p_node	*head;
	t_master	*master;

	head = ft_read_file(file_path);
	if (!head)
		return (NULL);
	master = ft_populate(head);
	ft_free_p_list(head);
	if (!master)
	{
		printf(RED "Master is NULL\n" RESET);
		return (NULL);
	}
	if (!ft_initmlx(&master))
		return (ft_free_master(master), NULL);
	return (master);
}
