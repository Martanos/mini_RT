/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:49:58 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 20:37:23 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_inrange(double value, double min, double max)
{
	if (isnan(value) || isnan(min) || isnan(max))
		return (false);
	return (value >= min && value <= max);
}

bool	ft_is_valid_vector(t_vect vector, double min, double max)
{
	return (ft_inrange(vector.x, min, max) && ft_inrange(vector.y, min, max)
		&& ft_inrange(vector.z, min, max));
}
