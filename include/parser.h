/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:24:10 by malee             #+#    #+#             */
/*   Updated: 2025/01/07 11:29:39 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "mini_rt.h"
typedef struct				s_parser_node;

typedef enum e_parser_type
{
	PARSER_TYPE_NONE = 0,
	PARSER_TYPE_STR = 1,
	PARSER_TYPE_DBL = 2,
	PARSER_TYPE_RGB_VAL = 3
}							t_parser_type;

typedef struct s_parser_node
{
	t_parser_type			type;
	char					*str;
	double					*dbl;
	uint32_t				*rgb_val;
	struct s_parser_node	*next;
}							t_parser_node;

t_parser_node				*ft_create_parser_node(char *str, double *dbl,
								uint32_t *rgb_val);
void						ft_add_parser_node(t_parser_node **head,
								t_parser_node *new_node);
void						ft_free_parser_list(t_parser_node *head);
void						ft_parser_exit(void);

#endif
