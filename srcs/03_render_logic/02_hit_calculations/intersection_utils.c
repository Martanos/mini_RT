/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:05:04 by malee             #+#    #+#             */
/*   Updated: 2025/03/06 14:54:33 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	ft_quadratic_find_closest_t(t_ray **ray, t_hit **hit, t_quadratic *quad,
		double *t)
{
	if (quad->t1 >= (*ray)->t_min && quad->t1 <= (*ray)->t_max
		&& quad->t1 < (*hit)->t)
	{
		*t = quad->t1;
		return (true);
	}
	else if (quad->t2 >= (*ray)->t_min && quad->t2 <= (*ray)->t_max
		&& quad->t2 < (*hit)->t)
	{
		*t = quad->t2;
		return (true);
	}
	return (false);
}
