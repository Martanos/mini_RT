/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:24:10 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 13:10:24 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "mini_rt.h"
typedef struct			s_p_node;
typedef struct			s_id_list;

typedef struct s_p_node
{
	ssize_t				line;
	ssize_t				pos;
	char				val;
	t_p_node			*next;
	t_p_node			*down;
}						t_p_node;

typedef struct s_id_list
{
	char				*id;
	struct s_id_list	*next;
}						t_id_list;

// Read File
t_p_node				*ft_read_file(char *file_path);

// Read File Utils
int						ft_verify_file_path(char *file_path);
t_p_node				*ft_gnl(int fd);
void					ft_number_raw_data(t_p_node *head);
t_p_node				*ft_clean_data(t_p_node *head);

// Table Creation
t_p_node				*ft_create_table(t_p_node *cur);

// Populate

// verifying
bool					ft_inrange(double value, double min, double max);
// Populate
t_master				*ft_populate(t_p_node *head);

// Structure UTILS
t_p_node				*ft_create_p_node(ssize_t line, ssize_t pos, char val);
void					ft_add_p_node(t_p_node **head, t_p_node *new_node);
void					ft_free_p_list(t_p_node *head);

// Utils
void					ft_skip_spaces(t_p_node **cur);
t_vect					*ft_get_xyz(t_p_node **cur);
double					ft_atod(t_p_node **cur);

// ERROR UTILS
bool					ft_format_error(t_p_node *head, char *message);
void					ft_warning(t_p_node *head, char *message);

#endif
