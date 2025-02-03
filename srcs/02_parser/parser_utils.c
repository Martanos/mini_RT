/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:49:58 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 17:44:44 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_inrange(double value, double min, double max)
{
	if (isnan(value) || isnan(min) || isnan(max))
		return (false);
	return (value >= min && value <= max);
}
