/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/16 10:46:06 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/16 19:27:48 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static void	ft_remove(char ***ev, int n)
{
	char	**new;
	char	**tmp;
	int		i;
	size_t	j;
	int		x;

	i = 0;
	x = 0;
	tmp = *ev;
	ft_checknull(new = ft_realloctab(tmp, 2, &j));
	while (i + x < (int)j)
	{
		if (i + x == n)
			x++;
		new[i] = tmp[i + x];
		i++;
	}
	free(tmp[n]);
	free(tmp);
	*ev = new;
}

int			ft_unsetenv(char ***ev, char **av)
{
	size_t	i;
	int		ret;
	size_t	j;
	int		n;

	i = 0;
	ret = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
			j++;
		n = ft_findenv(av[i], *ev, j);
		if (n != -1)
			ft_remove(ev, n);
		else
			ft_error(4, av[i]);
		i++;
	}
	return (ret);
}
