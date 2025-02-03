/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:25:47 by malee             #+#    #+#             */
/*   Updated: 2025/02/03 15:19:07 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "mini_rt.h"

void	ft_exit(t_master *master, char *error_message);
void	ft_free_master(t_master *master);
bool	ft_is_space(char c);

#endif
