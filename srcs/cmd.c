/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/01 15:21:39 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/16 19:20:42 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

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
	(void)ev;
	ft_putstr("$> ");
}

void		ft_docmd(char ***ev)
{
	char	**tab;
	int		ret;

	while (42)
	{
		ret = 0;
		ft_putprompt(*ev);
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
			ft_freeline(tab);
		}
		tab = NULL;
	}
}
