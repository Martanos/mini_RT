/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 00:08:03 by malee             #+#    #+#             */
/*   Updated: 2023/09/17 20:33:58 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Allocates (with malloc(3)) and returns a string
	representing the integer received as an argument.
	Negative numbers must be handled
*/

#include "libft.h"

static char	*ft_strrev(char *str)
{
	int		idx;
	int		size;
	char	tmp;

	size = ft_strlen(str);
	idx = 0;
	while (idx < (size / 2))
	{
		tmp = str[idx];
		str[idx] = str[size - idx - 1];
		str[size - idx - 1] = tmp;
		idx++;
	}
	return (str);
}

static int	ft_intlen(int n)
{
	int			idx;
	long long	tmp;

	tmp = n;
	idx = 1;
	if (tmp < 0)
	{
		tmp = tmp * -1;
		idx++;
	}
	while (tmp >= 10)
	{
		tmp = tmp / 10;
		idx++;
	}
	return (idx);
}

static void	set_n(int *is_negative, unsigned int *positive_n, int n)
{
	if (n < 0)
	{
		*is_negative = 1;
		*positive_n = -n;
	}
	else
	{
		*is_negative = 0;
		*positive_n = n;
	}
}

char	*ft_itoa(int n)
{
	int				idx;
	int				is_negative;
	unsigned int	positive_n;
	char			*value;

	if (n == 0)
		return (ft_strdup("0"));
	value = (char *)malloc(sizeof(char) * (ft_intlen(n) + 1));
	if (value == NULL)
		return (NULL);
	ft_memset(value, '\0', (ft_intlen(n) + 1));
	set_n(&is_negative, &positive_n, n);
	idx = 0;
	while (positive_n != 0)
	{
		value[idx++] = (positive_n % 10) + '0';
		positive_n = positive_n / 10;
	}
	if (is_negative)
		value[idx++] = '-';
	return (ft_strrev(value));
}
