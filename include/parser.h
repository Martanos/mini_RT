/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:24:10 by malee             #+#    #+#             */
/*   Updated: 2025/01/27 15:22:04 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "mini_rt.h"
typedef struct		s_p_node;
typedef struct		s_id_list;

typedef struct s_p_node
{
	ssize_t			line;
	ssize_t			pos;
	char			val;
	struct s_p_node	*next;
}					t_p_node;

t_p_node			*ft_read_file(char *file_path);
t_p_node			*ft_create_list(int fd);
void				ft_reconstructor(t_p_node **head);

// verifying
bool				ft_inrange(double value, double min, double max);

// Individual element checks
bool				ft_a_check(t_parser_node **cur, t_id_list *id_list,
						ssize_t *line);
bool				ft_c_check(t_parser_node **cur, t_id_list *id_list,
						ssize_t *line);
bool				ft_l_check(t_parser_node **cur, t_id_list *id_list,
						ssize_t *line);
bool				ft_sp_check(t_parser_node **cur, t_id_list *id_list,
						ssize_t *line);
bool				ft_pl_check(t_parser_node **cur, t_id_list *id_list,
						ssize_t *line);
bool				ft_cy_check(t_parser_node **cur, t_id_list *id_list,
						ssize_t *line);

// Read File
t_p_node			*ft_read_file(char *file_path);
static int			ft_verify_file_path(char *file_path);

// Populate
void				ft_populate(t_master *master, t_p_node *head);

// Structure UTILS
t_p_node			*ft_create_p_node(ssize_t line, ssize_t pos, char val);
void				ft_add_p_node(t_p_node **head, t_p_node *new_node);
void				ft_free_p_list(t_p_node *head);

// Utils
bool				ft_check_xyz(char *str);
bool				ft_check_rgb(char *str);
double				ft_atod(t_p_node **cur);

// ERROR UTILS
bool				ft_format_error(t_p_node *head, char *message);
void				ft_warning(t_p_node *head, char *message);

#endif
