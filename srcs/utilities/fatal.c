/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:40:11 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 11:50:17 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
** @brief Le nuker
** @param msg error message
*/
void	ft_fatal(char *msg)
{
	ft_putendl_fd(RED "Error", 2);
	ft_putendl_fd(msg, 2);
	ft_putendl_fd("This is a fatal error there may be memory leaks", 2);
	ft_putendl_fd(RESET, 2);
	exit(1);
}
