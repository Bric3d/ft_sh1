/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/01 15:21:39 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/15 17:41:59 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void	ft_freeline(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL && tab[i][0] != '\0')
		free(tab[i++]);
	free(tab);
}

char	**ft_getline(void)
{
	char	*input;
	char	**tab;

	input = NULL;
	get_next_line(0, &input);
	tab = ft_split(input);
	free(input);
	return (tab);
}

void	ft_docmd(char ***ev)
{
	char	**tab;

	(void)ev;
	
	while (42)
	{
		ft_putstr("$> ");
		tab = ft_getline();
		if (ft_builtins(ev, tab) == 0)
			ft_execve(*ev, tab, *ev);
		ft_freeline(tab);
		tab = NULL;
	}
}