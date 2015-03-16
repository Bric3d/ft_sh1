/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/01 14:57:13 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/16 15:37:56 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int		ft_findenv(char *var, char **ev, int i)
{
	int j;

	j = 0;
	if (ev == NULL || var == NULL)
		return (-1);
	while (ev[j])
	{
		if (ft_strncmp(ev[j], var, i) == 0 && ev[j][i] == '=')
			return (j);
		j++;
	}
	return (-1);
}

void	ft_checknull(void *stuff)
{
	if (stuff != NULL)
		return ;
	ft_error(5, NULL);
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