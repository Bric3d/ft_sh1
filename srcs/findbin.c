/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findbin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 11:07:20 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/10 13:50:43 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static char	*ft_binstat(char *binpath)
{
	struct stat	stat;

	if (lstat(binpath, &stat) == 0)
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
		ret[i + x] = '\0';
		return (ft_binstat(ret));
	}
	return (NULL);
}

char		*ft_findbin(char **ev, char **av)
{
	int 	i;
	int 	j;
	int		n;
	char	*tmp;
	char	*ret;


	n = ft_strlen(av[0]);
	ret = NULL;
	i = ft_findenv("PATH=", ev);
	if (i == -1)
	{
		ft_error(1, NULL);
		return(ret);
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
