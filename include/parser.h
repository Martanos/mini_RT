/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:24:10 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 20:08:17 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "mini_rt.h"
typedef struct	s_f_node;
typedef struct	s_p_node;
typedef struct	s_id_list;

// FILE NODE
typedef struct s_f_node
{
	char		val;
	t_f_node	*next;
}				t_f_node;

// PARSER NODE
typedef struct s_p_node
{
	char		*str;
	t_p_node	*next;
}				t_p_node;

// Read File
t_p_node		*ft_read_file(char *file_path);

// Read File Utils
int				ft_verify_file_path(char *file_path);
t_f_node		*ft_gnl(int fd);
t_f_node		*ft_clean_data(t_f_node *head);
t_f_node		*ft_create_f_node(char val);
void			ft_add_f_node(t_f_node **head, t_f_node *new_node);
void			ft_free_f_list(t_f_node *head);

// Populate

// verifying
bool			ft_inrange(double value, double min, double max);
// Populate
t_master		*ft_populate(t_p_node *head);

// Object Creation
bool			ft_create_amb(t_master **master, t_p_node **cur);
bool			ft_create_cam(t_master **master, t_p_node **cur);
bool			ft_create_light(t_master **master, t_p_node **cur);
bool			ft_create_plane(t_master **master, t_p_node **cur);
bool			ft_create_cylinder(t_master **master, t_p_node **cur);
bool			ft_create_cone(t_master **master, t_p_node **cur);

// SPHERE OBJECT CREATION UTILS
bool			ft_create_sphere(t_master **master, t_p_node **cur);
bool			ft_add_sphere_texture(t_master **master, t_sphere **sphere,
					char *str);
bool			ft_add_sphere_bump_map(t_master **master, t_sphere *sphere,
					char *str);
bool			ft_add_sphere_material(t_sphere **sphere, char *str);
bool			ft_add_populate_texture(t_master **master, t_sphere **sphere,
					char **split);

// Structure UTILS
t_p_node		*ft_create_p_node(char *str);
void			ft_add_p_node(t_p_node **head, t_p_node *new_node);
void			ft_free_p_list(t_p_node *head);

// Utils
t_vect			ft_get_xyz(t_p_node **cur);
double			ft_atod(char *str);
uint32_t		ft_get_rgb(char *str);

// ERROR UTILS
bool			ft_format_error(char *message);
void			ft_warning(char *message);

#endif
