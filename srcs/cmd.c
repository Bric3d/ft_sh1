/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/01 15:21:39 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/17 16:43:16 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

char		**g_env;

static void	ft_freeline(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL && tab[i][0] != '\0')
		free(tab[i++]);
	free(tab);
}

static char	**ft_getline(int *ret)
{
	char	*input;
	char	**tab;

	tab = NULL;
	input = NULL;
	if ((*ret = get_next_line(0, &input)) > 0)
	{
		tab = ft_split(input);
		free(input);
	}
	return (tab);
}

static void	ft_putprompt(char **ev)
{
	int		home;
	int		pwd;
	int		len;
	char	*prompt;

	home = ft_findenv("HOME", ev, 4);
	pwd = ft_findenv("PWD", ev, 3);
	ft_putstr("\r\033[33m");
	if (pwd != -1 && home != -1
		&& (prompt = ft_strstr(&ev[pwd][4], &ev[home][5])) != NULL)
	{
		len = ft_strlen(&ev[home][5]);
		ft_putchar('~');
		if (prompt[len] != '/')
			ft_putchar('/');
		ft_putstr(&prompt[len]);
	}
	else if (pwd != -1)
		ft_putstr(&ev[pwd][4]);
	ft_putstr("\033[32m");
	ft_putstr(" $> ");
	ft_putstr("\033[0m");
}

void		ft_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		ft_putprompt(g_env);
	}
}

void		ft_docmd(char ***ev)
{
	char	**tab;
	int		ret;

	while (42)
	{
		ret = 0;
		ft_putprompt(*ev);
		g_env = *ev;
		tab = ft_getline(&ret);
		if (ret == 0)
		{
			ft_putchar('\n');
			ft_exit(NULL);
		}
		if (tab)
		{
			if (ft_builtins(ev, tab) == 0)
				ft_execve(*ev, tab, *ev);
			else
				g_env = *ev;
			ft_freeline(tab);
		}
		tab = NULL;
	}
}
