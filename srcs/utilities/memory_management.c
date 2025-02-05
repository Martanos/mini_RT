/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 21:46:05 by malee             #+#    #+#             */
/*   Updated: 2025/02/05 20:37:06 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
** @brief Calculates the offset of a member in a structure
** @param ptr pointer to the structure
** @param member pointer to the member
** @return offset of the member
*/
size_t	ft_offsetof(void *base, void *member)
{
	return ((size_t)((char *)member - (char *)base));
}

/*
** @brief Frees a list of objects with a generic structure
** @param head pointer to the head of the list
** @param offset_next offset of the next pointer
** @param offset_pro offset of the object properties
*/
void	ft_free_list_generic(void *head, size_t offset_next, size_t offset_pro)
{
	void		*current;
	void		*temp;
	void		*next_ptr;
	t_obj_pro	*pro_ptr;

	current = head;
	while (current)
	{
		temp = current;
		next_ptr = NULL;
		if (offset_next)
			next_ptr = *(void **)((char *)current + offset_next);
		if (offset_pro)
		{
			pro_ptr = (t_obj_pro *)((char *)current + offset_pro);
			ft_free_obj_pro(pro_ptr);
		}
		current = next_ptr;
		free(temp);
	}
}
