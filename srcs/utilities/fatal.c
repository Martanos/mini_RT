/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:40:11 by malee             #+#    #+#             */
/*   Updated: 2025/01/10 17:49:33 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
** @brief Le nuker
** @param msg error message
*/
void	ft_fatal(char *msg)
{
	ft_putstr_fd(RED "Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\nThis is a fatal error expect leaks\n", 2);
	ft_putstr_fd(RESET, 2);
	exit(1);
}
