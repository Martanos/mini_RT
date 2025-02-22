/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:13:57 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 22:06:39 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc == 2)
	{
		scene = ft_parser(argv[1]);
		if (!scene)
			return (1);
		ft_render_scene(scene);
		ft_free_scene(scene);
	}
	else
	{
		printf(RED "Error\nInvalid number of arguments\n" RESET);
		return (1);
	}
	return (0);
}
