/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 21:07:08 by malee             #+#    #+#             */
/*   Updated: 2023/09/11 21:07:09 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Convert alpha character to lower case version*/

#include "libft.h"

int	ft_tolower(int input)
{
	if (input >= 65 && input <= 90)
		return (input + 32);
	return (input);
}
