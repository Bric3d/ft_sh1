/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 14:37:19 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/16 19:27:05 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static int	ft_place(char ***ev, char *var)
{
	size_t	j;
	char	**new;
	char	**tmp;
	size_t	i;

	i = 0;
	tmp = *ev;
	ft_checknull(new = ft_realloctab(tmp, 1, &j));
	while (i < j)
	{
		new[i] = tmp[i];
		i++;
	}
	free(tmp);
	new[j] = ft_strdup(var);
	new[j + 1] = NULL;
	*ev = new;
	return (1);
}

static int	ft_replace(int j, char **ev, char *var)
{
	free(ev[j]);
	ft_checknull(ev[j] = ft_strdup(var));
	return (1);
}

int			ft_setenv(char ***ev, char *var)
{
	size_t	i;
	int		ret;
	int		j;

	ret = 0;
	i = 0;
	if (var)
	{
		while (var[i] && var[i] != '=')
			i++;
		if (var[i] == '=')
		{
			j = ft_findenv(var, *ev, i);
			if (j != -1)
				ret = ft_replace(j, *ev, var);
			else
				ret = ft_place(ev, var);
		}
	}
	return (ret);
}

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
			ft_checknull(ev[j] = ft_strdup(var));
			ret = 1;
			break ;
		}
		j++;
	}
	if (ev[j] == NULL)
	{
		ft_checknull(ev[j] = ft_strdup(var));
		ret = 1;
	}
	return (ret);
}

int			ft_putenv(char **ev, char *var, int param)
{
	size_t	i;
	int		ret;

	ret = 0;
	i = 0;
	if (!ev)
	{
		ft_checknull(ev = (char **)ft_memalloc(sizeof(char *) * 2));
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
