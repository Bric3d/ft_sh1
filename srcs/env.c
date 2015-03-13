/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 16:08:10 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/09 16:38:49 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static void	ft_envcpy(char **ev, char **trueenv, char **av, int n)
{
	int	i;

	i = 0;
	if (trueenv != NULL)
		while (trueenv[i])
			ft_setenv(ev, trueenv[i++], 1);
	if (av && av[0] && av[1] && ft_strcmp(av[1], "-i") == 0)
		i = 2;
	else
		i = 1;
	if (av && av [1] && av[i])
		while (av[i] && i < n)
			ft_setenv(ev, av[i++], 1);
}

static int	ft_countlines(char **trueenv, char **av, int *n, int j)
{
	int	i;

	i = 0;
	while (trueenv && trueenv[i])
		i++;
	*n = j;
	while (av[j] && ft_strchr(av[j], '=') != NULL)
		j++;
	i = j - *n + i;
	*n = j;
	return (i);
}

static char	**ft_doenv(char **trueenv, char **av, int *n)
{
	int		j;
	char	**ev;

	j = 1;
	if (av[1] && ft_strcmp(av[1], "-i") == 0)
		trueenv = NULL, j++;
	j = ft_countlines(trueenv, av, n, j);
	ft_checknull(ev = (char **)ft_memalloc(sizeof(char *) * j + 1));
	ev[j] = NULL;
	ft_envcpy(ev, trueenv, av, *n);
	return (ev);
}

void		ft_env(char **trueenv, char **av)
{
	char	**ev;
	int		n;
	int		i;
	int		mode;

	i = 0;
	n = 0;
	mode = 1;
	ev = ft_doenv(trueenv, av, &n);
	if (av[n])
		ft_execve(trueenv, av, ev);
	while (ev[i])
	{
		if (mode == 1)
			ft_putendl(ev[i]);
		free(ev[i++]);
	}
	free(ev);
}