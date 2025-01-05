/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:27:02 by malee             #+#    #+#             */
/*   Updated: 2023/09/11 20:27:03 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Checks if input is a alphanumerical character */

#include "libft.h"

int	ft_isalnum(int input)
{
	if ((input >= 'A' && input <= 'Z') || (input >= 'a' && input <= 'z')
		|| (input >= '0' && input <= '9'))
		return (1);
	return (0);
}
