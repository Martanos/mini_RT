/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:13:57 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 22:05:50 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	main(int argc, char **argv)
{
	t_master	*master;

	if (argc == 2)
	{
		master = ft_parser(argv[1]);
		if (!master)
			return (1);
		ft_print_master(master);
		ft_render_scene(master);
		ft_free_master(master);
	}
	else
	{
		printf(RED "Error\nInvalid number of arguments\n" RESET);
		return (1);
	}
	return (0);
}
