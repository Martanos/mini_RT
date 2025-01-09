/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_verify.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:52:02 by malee             #+#    #+#             */
/*   Updated: 2025/01/09 17:36:18 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	ft_format_error(ssize_t line, char *msg, char *str)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("At line: ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd("\n", 2);
	if (str)
	{
		ft_putstr_fd("Character: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
	}
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	ft_putstr_fd(RESET, 2);
	return (false);
}

static bool	ft_id_is_alpha(char *str, ssize_t *line)
{
	while (*str)
	{
		if (!ft_isalpha(*str))
			return (ft_format_error(line,
					"Identifier must contain only alphabetic characters", str));
		str++;
	}
	return (true);
}

static bool	ft_verify_line(t_parser_node **cur, ssize_t *line,
		t_id_list **id_list)
{
	if (!ft_id_is_alpha((*cur)->str, line))
		return (false);
	if ((*cur)->str[0] == 'A' && (*cur)->str[1] == '\0')
		return (ft_a_check(cur, id_list, line));
	if ((*cur)->str[0] == 'C' && (*cur)->str[1] == '\0')
		return (ft_c_check(cur, id_list, line));
	if ((*cur)->str[0] == 'L' && (*cur)->str[1] == '\0')
		return (ft_l_check(cur, id_list, line));
	if (strncmp((*cur)->str, "sp", 2) == 0 && (*cur)->str[2] == '\0')
		return (ft_s_check(cur, id_list, line));
	if (strncmp((*cur)->str, "pl", 2) == 0 && (*cur)->str[2] == '\0')
		return (ft_pl_check(cur, id_list, line));
	if (strncmp((*cur)->str, "cy", 2) == 0 && (*cur)->str[2] == '\0')
		return (ft_cy_check(cur, id_list, line));
	return (ft_format_error(line, "Unknown identifier: ", (*cur)->str));
}

/*
** @brief Verifies the syntax of the parser node list
** @param head pointer to the head of the list
** @return true if the syntax is valid, false otherwise
*/
bool	ft_verify_syntax(t_parser_node *head)
{
	t_parser_node	*cur;
	ssize_t			line;
	t_id_list		*id_list;

	cur = head;
	line = 1;
	id_list = NULL;
	while (cur)
	{
		if (!ft_verify_line(&cur, &line, &id_list))
			return (false);
		line++;
		if (cur)
			cur = cur->next;
	}
	return (true);
}
