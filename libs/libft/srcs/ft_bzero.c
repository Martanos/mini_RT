/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:02:13 by malee             #+#    #+#             */
/*   Updated: 2023/09/13 21:05:40 by malee            ###   ########.fr       */
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
