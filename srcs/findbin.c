/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findbin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 11:07:20 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/16 18:58:33 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static char	*ft_binstat(char *binpath)
{
	struct stat	stat;

	if (lstat(binpath, &stat) == 0 && (S_ISREG(stat.st_mode)
		|| S_ISLNK(stat.st_mode)))
		return (binpath);
	else
	{
		free(binpath);
		return (NULL);
	}
}

static char	*ft_joinbin(char *path, int j, char *binname, int n)
{
	char	*ret;
	int		i;
	int		x;

	if (path && binname)
	{
		i = 0;
		x = 0;
		ft_checknull(ret = (char *)ft_memalloc(sizeof(char) * (j + n + 1)));
		while (i < j)
			ret[i] = path[i], i++;
		ret[i] = '/', i++;
		while (x < n)
			ret[i + x] = binname[x], x++;
		ret[i + x] = 0;
		return (ft_binstat(ret));
	}
	return (NULL);
}

static char	*ft_findsysbin(char **av, char **ev, char *ret, int n)
{
	char	*tmp;
	int		j;
	int		i;

	if ((i = ft_findenv("PATH", ev, 4)) == -1)
	{
		ft_error(1, NULL);
		return (ret);
	}
	tmp = &ev[i][5];
	while (ret == NULL)
	{
		j = 0;
		while (tmp[j] && tmp[j] != ':')
			j++;
		ret = ft_joinbin(tmp, j, av[0], n);
		if (tmp[j])
			j++;
		else
			break ;
		tmp = &tmp[j];
	}
	return (ret);
}

static char	*ft_findlocalbin(char **av, char *ret)
{
	ret = ft_strdup(av[0]);
	ret = ft_binstat(ret);
	return (ret);
}

char		*ft_findbin(char **ev, char **av)
{
	int		n;
	char	*ret;

	n = ft_strlen(av[0]);
	ret = NULL;
	if (ft_strncmp(av[0], ".", 1) == 0 || ft_strncmp(av[0], "/", 1) == 0)
		ret = ft_findlocalbin(av, ret);
	else
		ret = ft_findsysbin(av, ev, ret, n);
	return (ret);
}
