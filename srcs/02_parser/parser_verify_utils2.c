/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_verify_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:05:35 by malee             #+#    #+#             */
/*   Updated: 2025/01/09 18:37:28 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_a_check(t_parser_node **cur, t_id_list *id_list, ssize_t *line)
{
	if (ft_dup_check(id_list, (*cur)->str))
		return (ft_format_error(*line, "Identifier must be unique",
				(*cur)->str));
	ft_add_id(id_list, (*cur)->str);
	(*cur)->type = PARSER_TYPE_A;
	(*cur) = (*cur)->next;
	if (!ft_is_double(&(*cur)->str))
		return (ft_format_error(*line, "Invalid lighting ratio [0.0 - 1.0]",
				(*cur)->str));
	(*cur)->type = PARSER_TYPE_L_RATIO;
	(*cur) = (*cur)->next;
	if (!ft_check_xyz(&(*cur)->str))
		return (ft_format_error(*line, "Invalid coordinates", (*cur)->str));
	(*cur)->type = PARSER_TYPE_COORD;
	(*cur) = (*cur)->next;
	if ((*cur)->type != PARSER_TYPE_NEWLINE)
		return (ft_format_error(*line, "Invalid ambient lighting format",
				(*cur)->str));
	return (true);
}

bool	ft_c_check(t_parser_node **cur, t_id_list *id_list, ssize_t *line)
{
	if (ft_dup_check(id_list, (*cur)->str))
		return (ft_format_error(*line, "Identifier must be unique",
				(*cur)->str));
	ft_add_id(id_list, (*cur)->str);
	(*cur)->type = PARSER_TYPE_C;
	(*cur) = (*cur)->next;
	if (!ft_check_xyz(&(*cur)->str))
		return (ft_format_error(*line, "Invalid coordinates", (*cur)->str));
	(*cur)->type = PARSER_TYPE_COORD;
	(*cur) = (*cur)->next;
	if (!ft_check_xyz(&(*cur)->str))
		return (ft_format_error(*line, "Invalid normal vectors", (*cur)->str));
	(*cur)->type = PARSER_TYPE_VECTOR;
	(*cur) = (*cur)->next;
	if (ft_is_double(&(*cur)->str))
		return (ft_format_error(*line, "Invalid FOV", (*cur)->str));
	(*cur)->type = PARSER_TYPE_FOV;
	(*cur) = (*cur)->next;
	if ((*cur)->type != PARSER_TYPE_NEWLINE)
		return (ft_format_error(*line, "Invalid camera format", (*cur)->str));
	return (true);
}

bool	ft_l_check(t_parser_node **cur, t_id_list *id_list, ssize_t *line)
{
	if (ft_dup_check(id_list, (*cur)->str))
		return (ft_format_error(*line, "Identifier must be unique",
				(*cur)->str));
	ft_add_id(id_list, (*cur)->str);
	(*cur)->type = PARSER_TYPE_L;
	(*cur) = (*cur)->next;
	if (!ft_check_xyz(&(*cur)->str))
		return (ft_format_error(*line, "Invalid coordinates", (*cur)->str));
	(*cur)->type = PARSER_TYPE_COORD;
	(*cur) = (*cur)->next;
	if (!ft_is_double(&(*cur)->str))
		return (ft_format_error(*line, "Invalid lighting ratio [0.0 - 1.0]",
				(*cur)->str));
	(*cur)->type = PARSER_TYPE_L_RATIO;
	(*cur) = (*cur)->next;
	if (!ft_check_rgb(&(*cur)->str))
		return (ft_format_error(*line, "Invalid RGB format", (*cur)->str));
	(*cur)->type = PARSER_TYPE_RGB_VAL;
	(*cur) = (*cur)->next;
	if ((*cur)->type != PARSER_TYPE_NEWLINE)
		return (ft_format_error(*line, "Invalid light format", (*cur)->str));
	return (true);
}

bool	ft_sp_check(t_parser_node **cur, t_id_list *id_list, ssize_t *line)
{
	(*cur) = (*cur)->next;
	if (!ft_check_xyz(&(*cur)->str))
		return (ft_format_error(*line, "Invalid coordinates", (*cur)->str));
	(*cur)->type = PARSER_TYPE_COORD;
	(*cur) = (*cur)->next;
	if (!ft_is_double(&(*cur)->str))
		return (ft_format_error(*line, "Invalid diameter", (*cur)->str));
	(*cur)->type = PARSER_TYPE_DIAMETER;
	(*cur) = (*cur)->next;
	if (!ft_check_rgb(&(*cur)->str))
		return (ft_format_error(*line, "Invalid RGB format", (*cur)->str));
	(*cur)->type = PARSER_TYPE_RGB_VAL;
	(*cur) = (*cur)->next;
	if ((*cur)->type != PARSER_TYPE_NEWLINE)
		return (ft_format_error(*line, "Invalid sphere format", (*cur)->str));
	return (true);
}

bool	ft_pl_check(t_parser_node **cur, t_id_list *id_list, ssize_t *line)
{
	(*cur) = (*cur)->next;
	if (!ft_check_xyz(&(*cur)->str))
		return (ft_format_error(*line, "Invalid coordinates", (*cur)->str));
	(*cur)->type = PARSER_TYPE_COORD;
	(*cur) = (*cur)->next;
	if (!ft_check_xyz(&(*cur)->str))
		return (ft_format_error(*line, "Invalid normal vectors", (*cur)->str));
	(*cur)->type = PARSER_TYPE_VECTOR;
	(*cur) = (*cur)->next;
	if (!ft_check_rgb(&(*cur)->str))
		return (ft_format_error(*line, "Invalid RGB format", (*cur)->str));
	(*cur)->type = PARSER_TYPE_RGB_VAL;
	(*cur) = (*cur)->next;
	if ((*cur)->type != PARSER_TYPE_NEWLINE)
		return (ft_format_error(*line, "Invalid plane format", (*cur)->str));
	return (true);
}

bool	ft_cy_check(t_parser_node **cur, t_id_list *id_list, ssize_t *line)
{
	(*cur) = (*cur)->next;
	if (!ft_check_xyz(&(*cur)->str))
		return (ft_format_error(*line, "Invalid coordinates", (*cur)->str));
	(*cur)->type = PARSER_TYPE_COORD;
	(*cur) = (*cur)->next;
	if (!ft_check_xyz(&(*cur)->str))
		return (ft_format_error(*line, "Invalid normal vectors", (*cur)->str));
	(*cur)->type = PARSER_TYPE_VECTOR;
	(*cur) = (*cur)->next;
	if (!ft_is_double(&(*cur)->str))
		return (ft_format_error(*line, "Invalid diameter", (*cur)->str));
	(*cur)->type = PARSER_TYPE_DIAMETER;
	(*cur) = (*cur)->next;
	if (!ft_is_double(&(*cur)->str))
		return (ft_format_error(*line, "Invalid height", (*cur)->str));
	(*cur)->type = PARSER_TYPE_HEIGHT;
	(*cur) = (*cur)->next;
	if (!ft_check_rgb(&(*cur)->str))
		return (ft_format_error(*line, "Invalid RGB format", (*cur)->str));
	(*cur)->type = PARSER_TYPE_RGB_VAL;
	(*cur) = (*cur)->next;
	if ((*cur)->type != PARSER_TYPE_NEWLINE)
		return (ft_format_error(*line, "Invalid cylinder format", (*cur)->str));
	return (true);
}
