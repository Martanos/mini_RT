/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:22:29 by malee             #+#    #+#             */
/*   Updated: 2025/03/04 15:39:28 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_add_obj(t_scene **scene, t_obj_data **obj)
{
	t_obj_data	*temp;

	if ((*scene)->obj_head == NULL)
		(*scene)->obj_head = obj;
	else
	{
		temp = (*scene)->obj_head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = obj;
	}
}

static bool	ft_identify(t_scene **scene, t_p_node **cur)
{
	printf(GREEN "Identifying: %s\n" RESET, (*cur)->str);
	if (ft_strcmp((*cur)->str, "A") == 0)
		return (ft_create_amb(scene, cur));
	else if (ft_strcmp((*cur)->str, "C") == 0)
		return (ft_create_cam(scene, cur));
	else if (ft_strcmp((*cur)->str, "L") == 0)
		return (ft_create_obj(scene, cur, LIGHT));
	else if (ft_strcmp((*cur)->str, "pl") == 0)
		return (ft_create_obj(scene, cur, PLANE));
	else if (ft_strcmp((*cur)->str, "cy") == 0)
		return (ft_create_obj(scene, cur, CYLINDER));
	else if (ft_strcmp((*cur)->str, "sp") == 0)
		return (ft_create_obj(scene, cur, SPHERE));
	else if (ft_strcmp((*cur)->str, "co") == 0)
		return (ft_create_obj(scene, cur, CONE));
	return (ft_error("Invalid identifier"));
}

static bool	ft_initmlx(t_scene **scene)
{
	(*scene)->mlx_ptr = mlx_init();
	if (!(*scene)->mlx_ptr)
		return (ft_error("mlx failed to initialize"));
	(*scene)->win_ptr = mlx_new_window((*scene)->mlx_ptr, DEFAULT_WINDOW_WIDTH,
			DEFAULT_WINDOW_HEIGHT, "miniRT");
	if (!(*scene)->win_ptr)
		return (ft_error("mlx failed to create window"));
	(*scene)->img.img_ptr = mlx_new_image((*scene)->mlx_ptr,
			DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
	if (!(*scene)->img.img_ptr)
		return (ft_error("mlx failed to create image"));
	(*scene)->img.pixels_ptr = mlx_get_data_addr((*scene)->img.img_ptr,
			&(*scene)->img.bpp, &(*scene)->img.line_len, &(*scene)->img.endian);
	if (!(*scene)->img.pixels_ptr)
		return (ft_error("mlx failed to get image address"));
	mlx_clear_window((*scene)->mlx_ptr, (*scene)->win_ptr);
	return (true);
}

/*
** @brief Returns a master structure with the parsed data
** @param head pointer to the head of the parser node list
** @return false if successful, true if error
*/
t_scene	*ft_populate(t_p_node *cur)
{
	t_scene	*scene;

	scene = (t_scene *)ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (NULL);
	if (!ft_initmlx(&scene))
		return (ft_free_scene(scene), NULL);
	while (cur)
	{
		while (cur && cur->str && ft_isspace(cur->str[0]))
			cur = cur->next;
		if (!ft_identify(&scene, &cur))
			return (ft_free_scene(scene), NULL);
		while (cur && cur->str && ft_isspace(cur->str[0]))
			cur = cur->next;
	}
	return (scene);
}

static void	ft_print_p_list(t_p_node *head)
{
	printf(YELLOW "-----List to be parsed-----\n" RESET);
	while (head)
	{
		if (!head)
			printf(RED "head: [NULL]\n" RESET);
		else if (!head->str)
			printf(RED "str: [NULL]\n" RESET);
		else
			printf(GREEN "str: [%s]\n" RESET, head->str);
		head = head->next;
	}
}

/*
** @brief Facilitates the parsing of the file
** @param file_path path to the file
** @return pointer to the master structure
*/
t_scene	*ft_parser(char *file_path)
{
	t_p_node	*head;
	t_scene		*scene;

	head = ft_read_file(file_path);
	if (!head)
		return (NULL);
	ft_print_p_list(head);
	scene = ft_populate(head);
	ft_free_p_list(head);
	if (!scene)
		return (NULL);
	if (!scene->amb_data.set)
		return (ft_error("No ambient light found"), ft_free_scene(scene), NULL);
	if (!scene->cam_data.set)
		return (ft_error("No camera found"), ft_free_scene(scene), NULL);
	if (!scene->light_data)
		return (ft_error("No light found"), ft_free_scene(scene), NULL);
	return (scene);
}
