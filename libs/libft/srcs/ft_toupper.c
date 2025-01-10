/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 20:58:57 by malee             #+#    #+#             */
/*   Updated: 2024/06/01 20:50:58 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Convert alpha character to higher case version*/

#include "libft.h"

int	ft_toupper(int input)
{
	if (input >= 97 && input <= 122)
		return (input - 32);
	return (input);
}
