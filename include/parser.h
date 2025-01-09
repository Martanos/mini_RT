/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:24:10 by malee             #+#    #+#             */
/*   Updated: 2025/01/09 19:21:08 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "mini_rt.h"
typedef struct				s_parser_node;
typedef struct				s_id_list;

typedef enum e_parser_type
{
	PARSER_TYPE_NONE = 0,
	PARSER_TYPE_DIAMETER = 1,
	PARSER_TYPE_RGB_VAL = 2,
	PARSER_TYPE_COORD = 3,
	PARSER_TYPE_FOV = 4,
	PARSER_TYPE_VECTOR = 5,
	PARSER_TYPE_NEWLINE = 6,
	PARSER_TYPE_HEIGHT = 7,
	PARSER_TYPE_L_RATIO = 8,
	PARSER_TYPE_A = 9,
	PARSER_TYPE_C = 10,
	PARSER_TYPE_L = 11,
	PARSER_TYPE_SP = 12,
	PARSER_TYPE_PL = 13,
	PARSER_TYPE_CY = 14
}							t_parser_type;

typedef struct s_parser_node
{
	t_parser_type			type;
	char					*str;
	double					*dbl;

	uint32_t				*rgb_val;
	struct s_parser_node	*next;
}							t_parser_node;

typedef struct s_id_list
{
	char					*id;
	struct s_id_list		*next;
}							t_id_list;

t_parser_node				*ft_create_parser_node(t_parser_type type,
								char *str, double *dbl, uint32_t *rgb_val);
void						ft_add_parser_node(t_parser_node **head,
								t_parser_node *new_node);
void						ft_free_parser_list(t_parser_node *head);
t_parser_node				*ft_read_file(char *file_path);
t_parser_node				*ft_create_list(int fd);
void						ft_reconstructor(t_parser_node **head);
void						ft_add_id(t_id_list **id_list, char *str);
bool						ft_dup_check(t_id_list *id_list, char *str);

// verifying
bool						ft_verify_syntax(t_parser_node *head);
bool						ft_verify_line(t_parser_node **cur, ssize_t *line,
								t_id_list **id_list);

// Individual element checks
bool						ft_a_check(t_parser_node **cur, t_id_list *id_list,
								ssize_t *line);
bool						ft_c_check(t_parser_node **cur, t_id_list *id_list,
								ssize_t *line);
bool						ft_l_check(t_parser_node **cur, t_id_list *id_list,
								ssize_t *line);
bool						ft_sp_check(t_parser_node **cur, t_id_list *id_list,
								ssize_t *line);
bool						ft_pl_check(t_parser_node **cur, t_id_list *id_list,
								ssize_t *line);
bool						ft_cy_check(t_parser_node **cur, t_id_list *id_list,
								ssize_t *line);
// Errors
bool						ft_format_error(ssize_t line, char *msg, char *str);

// Utils
bool						ft_is_double(char **str);
bool						ft_check_xyz(char *str);
bool						ft_check_rgb(char *str);

#endif
