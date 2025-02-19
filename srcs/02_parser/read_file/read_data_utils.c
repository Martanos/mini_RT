/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 23:47:04 by malee             #+#    #+#             */
/*   Updated: 2025/02/19 17:48:43 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

size_t	ft_custom_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '#')
		i++;
	return (i);
}

bool	ft_add_to_node(t_p_node **head, char **buffer)
{
	char	*str_to_add;
	char	*temp;
	size_t	i;

	if (!head || !buffer)
		return (ft_error("Head or buffer is NULL"));
	temp = NULL;
	str_to_add = (char *)ft_calloc(sizeof(char), ft_custom_strlen(*buffer) + 1);
	if (!str_to_add)
		return (ft_error("Failed to allocate memory"));
	i = 0;
	while (**buffer && !ft_isspace(**buffer) && **buffer != '#')
	{
		str_to_add[i] = **buffer;
		(*buffer)++;
		i++;
	}
	temp = ft_strjoin((*head)->str, str_to_add);
	free((*head)->str);
	free(str_to_add);
	(*head)->str = ft_strdup(temp);
	free(temp);
	return (true);
}

bool	ft_add_new_node(t_p_node **head, char **buffer)
{
	char	*new_str;
	size_t	i;

	if (!head || !buffer)
		return (ft_error("Head or buffer is NULL"));
	new_str = (char *)ft_calloc(sizeof(char), ft_custom_strlen(*buffer) + 1);
	if (!new_str)
		return (ft_error("Failed to allocate memory"));
	i = 0;
	while (**buffer && !ft_isspace(**buffer) && **buffer != '#')
	{
		new_str[i] = **buffer;
		(*buffer)++;
		i++;
	}
	if (!ft_add_p_node(head, ft_create_p_node(new_str)))
		return (false);
	free(new_str);
	return (true);
}
