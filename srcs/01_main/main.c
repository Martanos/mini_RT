/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:13:57 by malee             #+#    #+#             */
/*   Updated: 2025/01/10 17:53:04 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

int	main(int argc, char **argv)
{
	t_master	*master;

	if (argc == 2)
	{
		master = ft_parse_file(argv[1]);
	}
	else
		ft_fatal("Invalid number of arguments");
	return (0);
}
