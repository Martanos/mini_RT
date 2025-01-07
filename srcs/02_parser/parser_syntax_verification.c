/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_verification.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:52:02 by malee             #+#    #+#             */
/*   Updated: 2025/01/07 20:26:22 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	ft_format_error(ssize_t line, ssize_t pos, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" at line: ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(" at position: ", 2);
	ft_putnbr_fd(pos, 2);
	ft_putstr_fd("\n", 2);
}

static bool	ft_verify_elements(t_parser_node **cur, ssize_t *line, ssize_t *pos,
		t_list **e_list)
{
	if (ft_strncmp((*cur)->str, "A", 1) == 0)
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
	ssize_t			pos;

	cur = head;
	line = 1;
	pos = 0;
	while (cur)
	{
		if (ft_isalpha(cur->str[0]))
			ft_verify_elements(&cur, &line, &pos);
		if (cur && cur->str[0] != '\n')
		{
			ft_format_error(line, pos, "Expected identifier");
			break ;
		}
		elseif(cur && cur->str[0] == '\n')
		{
			line++;
			pos = 0;
			cur = cur->next;
		}
	}
	return (true);
}
