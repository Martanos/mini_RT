/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 11:40:11 by malee             #+#    #+#             */
/*   Updated: 2025/01/07 11:48:10 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_fatal(void)
{
	ft_putstr_fd("Error\nFatal system error detected expect leaks\n", 2);
	perror(NULL);
	exit(1);
}
