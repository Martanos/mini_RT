/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_create_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:46:05 by malee             #+#    #+#             */
/*   Updated: 2025/01/10 22:11:46 by malee            ###   ########.fr       */
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

uint32_t	ft_create_rgb(t_p_node **head, bool **error, )
{
	return (r << 16 | g << 8 | b);
}

/*
** @brief Create an ambient light structure
** @param head The head of the linked list
** @param error The error flag
** @return The ambient light structure
*/
t_amb	ft_create_amb(t_p_node **head, bool **error)
{
	t_amb	amb;

	amb.ratio = ft_atod(head, error);
	amb.rgb = ft_atod(head, error);
	return (amb);
}
