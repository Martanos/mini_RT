/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:02:13 by malee             #+#    #+#             */
/*   Updated: 2025/01/10 18:22:46 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  The  bzero()  function  erases  the  data
	in the n bytes of the memory starting at the location
	pointed to by s, by writing zeros (bytes  containing
	'\0') to that area.
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
