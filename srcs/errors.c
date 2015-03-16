/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 17:53:01 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/16 15:38:01 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void	ft_error(int err, char *str)
{
	if (err == 1)
		ft_putendl_fd("sh1: Please set a PATH value using setenv", 2);
	if(err == 2 || err == 3 || err == 4)
	{
		ft_putstr_fd("sh1: ", 2);
		if (err == 2)
			ft_putstr_fd("permission denied: ", 2);
		else if (err == 3)
			ft_putstr_fd("command not found: ", 2);
		else if (err == 4)
			ft_putstr_fd("This environment variable does not exist: ", 2);
		ft_putendl_fd(str, 2);
	}
	if (err == 5)
		ft_putendl_fd("sh1: Something went wrong with malloc.", 2);
}
