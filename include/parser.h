/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:24:10 by malee             #+#    #+#             */
/*   Updated: 2025/02/22 22:45:22 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "mini_rt.h"
# define BUFFER_SIZE 1048576 // 1MB

typedef struct s_f_node	t_f_node;
typedef struct s_p_node	t_p_node;

/*
** @brief Property node structure
** @param str string value
** @param next pointer to the next property node
*/
typedef struct s_p_node
{
	char				*str;
	t_p_node			*next;
	t_p_node			*prev;
}						t_p_node;

// PARSER
t_scene					*ft_parser(char *file_path);

// Read File
t_p_node				*ft_read_file(char *file_path);

// Read File Utils
bool					ft_process_buffer(char *buffer, t_p_node **head);

// PARSER NODE UTILS
t_p_node				*ft_create_p_node(char *str);
bool					ft_add_p_node(t_p_node **head, t_p_node *new_node);
void					ft_free_p_list(t_p_node *head);

// Object Creation
t_scene					*ft_populate(t_p_node *head);
bool					ft_create_amb(t_scene **scene, t_p_node **cur);
bool					ft_create_cam(t_scene **scene, t_p_node **cur);
bool					ft_create_light(t_scene **scene, t_p_node **cur,
							t_obj_type type);
bool					ft_create_sphere(t_scene **scene, t_p_node **cur,
							t_obj_type type);
bool					ft_create_plane(t_scene **scene, t_p_node **cur,
							t_obj_type type);
bool					ft_create_cylinder(t_scene **scene, t_p_node **cur,
							t_obj_type type);
bool					ft_create_cone(t_scene **scene, t_p_node **cur,
							t_obj_type type);

// Property Creation
bool					ft_extra_data(t_scene **scene, t_obj_data **obj,
							t_p_node **cur);
bool					ft_add_texture(t_scene **scene, t_obj_data **obj,
							char *str);
bool					ft_add_bump_map(t_scene **scene, t_obj_data **obj,
							char *str);
bool					ft_add_material(t_obj_data **obj, char *str);

// Utils
t_vect					ft_get_xyz(t_p_node **cur);
double					ft_atod(char *str);
bool					ft_get_rgb(uint32_t *rgb, char *str);
bool					ft_is_valid_vector(t_vect vector, double min,
							double max, char *str);
bool					ft_next(t_p_node **cur, char *str);
bool					ft_inrange(double value, double min, double max);

// Parser Node Utils
t_p_node				*ft_create_p_node(char *str);
bool					ft_add_p_node(t_p_node **head, t_p_node *new_node);
void					ft_free_p_list(t_p_node *head);

// Parser Node Utils
t_p_node				*ft_last_p_node(t_p_node *head);
bool					ft_add_to_node(t_p_node **head, char **buffer);
bool					ft_add_new_node(t_p_node **head, char **buffer);

#endif
