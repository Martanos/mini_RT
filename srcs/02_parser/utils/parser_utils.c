/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:49:58 by malee             #+#    #+#             */
/*   Updated: 2025/03/21 23:36:11 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_inrange(double value, double min, double max)
{
	if (isnan(value) || isnan(min) || isnan(max))
		return (false);
	return (value >= min && value <= max);
}

bool	ft_is_valid_vector(t_vect vector, double min, double max, char *str)
{
	if (isnan(vector.x) || !ft_inrange(vector.x, min, max))
		return (ft_error(str));
	if (isnan(vector.y) || !ft_inrange(vector.y, min, max))
		return (ft_error(str));
	if (isnan(vector.z) || !ft_inrange(vector.z, min, max))
		return (ft_error(str));
	return (true);
}

bool	ft_next(t_p_node **cur, char *str)
{
	if ((*cur)->next == NULL || (*cur)->next->str == NULL
		|| (*cur)->next->str[0] == '\n')
		return (ft_error(str));
	(*cur) = (*cur)->next;
	return (true);
}
