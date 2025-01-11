/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_create_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:46:05 by malee             #+#    #+#             */
/*   Updated: 2025/01/11 16:58:50 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_sign_check(t_p_node **head, bool *error, double *num)
{
	if ((*head)->val == '-' || (*head)->val == '+')
	{
		if ((*head)->val == '-')
			*num = -0.0;
		(*head) = (*head)->next;
	}
	if (!ft_isdigit((*head)->val))
		return (ft_format_error(*head, "Invalid double", error));
	return (true);
}

/*
** @brief Convert a string to a double
** @param str The string to convert
** @return The double value
*/
double	ft_atod(t_p_node **head, bool **error)
{
	double	num;
	int		dot_count;

	num = 0.0;
	dot_count = 0;
	if (!ft_sign_check(head, error, &num))
		return (0.0);
	while (*head)
	{
		if ((*head)->val == '.')
		{
			if (++dot_count > 1)
				return (ft_format_error(*head, "Invalid double", error));
			(*head) = (*head)->next;
		}
		else if (!ft_isdigit((*head)->val))
			return (ft_format_error(*head, "Invalid double", error));
		if (dot_count == 0)
			num = num * 10 + ((*head)->val - '0');
		else
			num = num + ((*head)->val - '0') / pow(10, dot_count);
		(*head) = (*head)->next;
	}
	return (num);
}

uint32_t	ft_str_to_rgb_val(t_p_node **head, bool **error)
{
	int		spaces;
	uint8_t	r;

	r = 0;
	spaces = 0;
	while (*head && (*head)->val != ',')
	{
		if (!ft_isdigit((*head)->val))
			return (ft_format_error(*head,
					"Invalid RGB value,values must be between 0 and 255",
					error));
		r += (*head)->val - '0' * pow(10, spaces);
		spaces++;
		(*head) = (*head)->next;
		if (spaces > 2)
			return (ft_format_error(*head,
					"Invalid RGB value,values must be between 0 and 255",
					error));
	}
	return (r);
}

bool	ft_str_to_rgb(t_p_node **head, bool **error)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	r = ft_str_to_rgb_val(head, error);
	g = ft_str_to_rgb_val(head, error);
	b = ft_str_to_rgb_val(head, error);
	if (*head && (*head)->val != ''
	return (ft_create_rgb(r, g, b));
}

bool	ft_range(double num, double min, double max)
{
	if (num < min || num > max)
		return (false);
	return (true);
}

/*
** @brief Create an ambient light structure
** @param head The head of the linked list
** @param error The error flag
** @return The ambient light structure
*/
bool	ft_create_amb(t_master *master, t_p_node **head, bool **error)
{
	t_amb	amb;

	if (master->amb_head)
		return (ft_format_error(*head, "Ambient lighting object already exists",
				error));
	amb.ratio = ft_atod(head, error);
	if (!ft_range(amb.ratio, 0, 1))
		return (ft_format_error(*head,
				"Ambient lighting ratio must be between 0.0 and 1.0", error));
	amb.rgb = return (amb);
}
