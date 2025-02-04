/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:35:09 by malee             #+#    #+#             */
/*   Updated: 2025/02/04 14:22:18 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	ft_format_error(char *message)
{
	ft_putstr_fd(RED, 2);
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(message, 2);
	ft_putendl_fd(RESET, 2);
	return (false);
}

void	ft_warning(char *message)
{
	ft_putstr_fd(ORANGE, 2);
	ft_putendl_fd("Warning", 2);
	ft_putstr_fd(message, 2);
	ft_putendl_fd(RESET, 2);
}
