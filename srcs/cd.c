/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/16 10:45:49 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/17 11:40:14 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static void	ft_rewrite_path(char ***ev, char *pwd)
{
	int		i;
	char	*buf;
	char	**tmp;

	tmp = *ev;
	i = ft_findenv("PWD", tmp, 3);
	if (i > -1)
	{
		ft_checknull(buf = ft_strjoin("OLDPWD=", &tmp[i][4]));
		ft_setenv(ev, buf);
		free(buf);
		buf = NULL;
	}
	ft_checknull(buf = ft_strjoin("PWD=", pwd));
	ft_setenv(ev, buf);
	free(buf);
	buf = NULL;
}

static int	ft_chdir(char *path)
{
	struct stat		buf;
	int				ret;

	ret = -1;
	if (lstat(path, &buf) == -1)
		cderror(&path, 0);
	else if (!S_ISDIR(buf.st_mode) && !S_ISLNK(buf.st_mode))
		cderror(&path, 2);
	else if (!(buf.st_mode & S_IXUSR) && !(buf.st_mode & S_IXGRP)
		&& !(buf.st_mode & S_IXOTH))
		cderror(&path, 3);
	else if ((ret = chdir(path)) == -1)
		cderror(&path, 2);
	return (ret);
}

static void	cd1arg(char *path, char ***ev)
{
	static char current[1024];
	static char prev[1024];
	int			ret;

	ret = -1;
	if (!ft_strcmp(path, "-"))
	{
		if (*prev)
		{
			ft_bzero(current, 1024), getcwd(current, 1024);
			ret = ft_chdir(prev);
			ft_memcpy(prev, current, 1024);
		}
		else
			cderror(NULL, 5);
	}
	else
	{
		ft_bzero(prev, 1024), getcwd(prev, 1024);
		ret = ft_chdir(path);
	}
	ft_bzero(current, 1024), getcwd(current, 1024);
	if (ret == 0)
		ft_rewrite_path(ev, current);
}

static void	cd2args(char **av, char ***ev)
{
	(void)av;
	(void)ev;
	cd1arg(av[1], ev);
}

void		ft_cd(char **av, char ***ev)
{
	int		home;
	size_t	len;
	char	**tmp;

	tmp = *ev;
	len = ft_tablen(av) - 1;
	if (len > 2)
		cderror(av, 1);
	if (len > 2)
		return ;
	else if (len == 2)
		cd2args(av, ev);
	else if (len == 1)
		cd1arg(av[1], ev);
	else
	{
		if ((home = ft_findenv("HOME", tmp, 4)) >= 0)
			cd1arg(&tmp[home][5], ev);
		else
			cderror(NULL, 4);
	}
}
