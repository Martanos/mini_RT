/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_warnings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:05:12 by malee             #+#    #+#             */
/*   Updated: 2025/02/14 14:05:21 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_warning(char *message)
{
	ft_putstr_fd(ORANGE, 2);
	ft_putendl_fd("Warning", 2);
	ft_putstr_fd(message, 2);
	ft_putendl_fd(RESET, 2);
}
