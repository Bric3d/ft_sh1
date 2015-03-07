/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/01 14:57:13 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/02 12:38:53 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void	ft_checknull(void *stuff)
{
	if (stuff != NULL)
		return ;
	ft_putendl_fd("ft_minishell : Something went wrong with malloc.", 2);
	exit(-1);
}

char	**cloneenv(char **ev)
{
	char	**newev;

	if (ev != NULL)
		ft_checknull(newev = ft_tabdup(ev));
	else
		newev = NULL;
	return (newev);
}