/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 14:37:19 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/07 17:31:23 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static int	ft_searchnreplace(char **ev, char *var, int i)
{
	int	ret;
	int	j;

	ret = 0;
	j = 0;
	while (ev[j])
	{
		if (ft_strncmp(ev[j], var, i) == 0)
		{
			free(ev[j]);
			ev[j] = ft_strdup(var);
			ret = 1;
			break ;
		}
		j++;
	}
	if (ev[j] == NULL)
	{
		ev[j] = ft_strdup(var);
		ret = 1;
	}
	return (ret);
}

int			ft_setenv(char **ev, char *var, int param)
{
	size_t	i;
	int		ret;

	ret = 0;
	i = 0;
	if (!ev)
	{
		ev = (char **)ft_memalloc(sizeof(char *) * 2);
		ev[1] = NULL;
	}
	if (var && param == 1)
	{
		while (var[i] && var[i] != '=')
			i++;
		if (var[i] == '=')
			ret = ft_searchnreplace(ev, var, i);
	}
	return (ret);
}