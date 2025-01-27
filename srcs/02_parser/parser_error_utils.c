/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:35:09 by malee             #+#    #+#             */
/*   Updated: 2025/01/27 11:33:54 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_format_error(t_p_node *head, char *message)
{
	ft_putstr_fd(RED, 2);
	ft_putendl_fd("Error", 2);
	ft_putstr_fd("At line: ", 2);
	ft_putnbr_fd(head->line, 2);
	ft_putstr_fd(" position: ", 2);
	ft_putendl_fd(head->pos, 2);
	ft_putendl_fd(message, 2);
	ft_putstr_fd(RESET, 2);
}

void	ft_warning(t_p_node *head, char *message)
{
	ft_putstr_fd(ORANGE, 2);
	ft_putendl_fd("Warning", 2);
	ft_putstr_fd("At line: ", 2);
	ft_putnbr_fd(head->line, 2);
	ft_putstr_fd(" position: ", 2);
	ft_putendl_fd(head->pos, 2);
	ft_putstr_fd(message, 2);
	ft_putendl_fd(RESET, 2);
}