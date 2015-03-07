/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/01 17:18:43 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/02 15:44:49 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static size_t	ft_word_nb(char const *s)
{
	size_t	a;
	size_t	numb;
	int		b;

	b = 0;
	a = 0;
	numb = 0;
	while (s[b])
	{
		if (s[b] != ' ' && a == 0)
		{
			a = 1;
			numb++;
		}
		if (s[b] == ' ' && a == 1)
			a = 0;
		b++;
	}
	return (numb);
}

static void		ft_placestr(char **tab, char const *s)
{
	int		a;
	int		start;
	int		b;

	b = 0;
	start = 0;
	a = 0;
	while (s[b])
	{
		if (s[b] != ' ' && a == 0)
		{
			start = b;
			a = 1;
		}
		if (s[b] == ' ' && a == 1)
		{
			ft_checknull(*tab = ft_strsub(s, start, b - start));
			++tab;
			a = 0;
		}
		b++;
	}
	if (a == 1)
		ft_checknull(*tab = ft_strsub(s, start, b - start));
}

char		**ft_split(char const *s)
{
	char	**tab;
	size_t	nb;

	nb = 0;
	if (s == NULL)
		return (NULL);
	nb = ft_word_nb(s);
	tab = (char **)ft_memalloc(sizeof(char *) * (nb + 1));
	if (!tab)
		return (NULL);
	ft_placestr(tab, s);
	tab[nb] = '\0';
	return (tab);
}