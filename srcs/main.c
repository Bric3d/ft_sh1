/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/04 15:01:50 by bbecker           #+#    #+#             */
/*   Updated: 2015/01/11 20:17:43 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>

char	*ft_getenv(char **ev, char *elem, int param)
{
	int		i;
	int		n;
	char	*value;

	value = NULL;
	i = 0;
	n = 0;
	n = ft_strlen(elem);
	while (ev[i] && value == NULL)
		value = ft_strnstr(ev[i++], elem, n);
	if (!value)
		return (NULL);
	i = 0;
	if (param == 0)
		while (i < n)
			i++;
	if (param == 0)
		return (&value[i]);
	if (param == 1)
		return (value);
	return (NULL);
}
char	*pathjoin(char **ev, char *target, char *elem, int param)
{
	char	*ret;
	char	*current;
	char	*tmp;

	if (param == 0 && (current = ft_getenv(ev, elem, 0)) == NULL)
		return (NULL);
	if (param == 1)
		current = elem;
	if (target)
	{
		tmp = ft_strjoin(current, "/");
		ret = ft_strjoin(tmp, target);
		free(tmp);
	}
	else
		ret = ft_strdup(current);
	return (ret);
}

void	ft_switch(char **tab, char *str)
{
	ft_putendl("6");
	if (tab[1])
		free(tab[1]);
	ft_putendl("6");
	tab[1] = str;
}

DIR		*ft_dir(void *data, int param)
{
	DIR		*dir;
	int		error;

	dir = NULL;
	error = 0;
	if (data)
	{
		if (param == 0 || param == 2)
		{
			if ((dir = opendir((char *)data)) == NULL)
				error = -1;
			else
				return (dir);
		}
		if (param == 1 || param == 3)
		{
			if (closedir((DIR *)data) == -1)
				error = -1;
			else
				return (NULL);
		}
	}
	if (error == -1 && (param == 2 || param == 3))
		perror("error");
	return (NULL);
}

char	*ft_readdir(DIR *dir, char *bin, char *path, int param)
{
	struct dirent	*read;
	char			*ret;
	int				len;
	char			b;

	b = 'A';
	len = ft_strlen(bin);
	ret = NULL;
	read = NULL;
	if (dir && (path || param == 1) && bin)
	{
		while ((read = readdir(dir)) != NULL)
		{
			if (read->d_namlen == len && ft_strcmp(read->d_name, bin) == 0)
			{
				if (param == 0)
					ret = pathjoin(NULL, bin, path, 1);
				if (param == 1)
					ret = &b;
			}
		}
	}
	return (ret);
}

char	*localbin(char *str)
{
	char	*ret;
	DIR		*dir;

	ret = NULL;
	dir = NULL;
	dir = ft_dir("./", 0);
	ret = ft_readdir(dir, &str[2], "./", 0);
	dir = ft_dir(dir, 1);
	return (ret);
}

void	ft_nobin(char *bin, char *ret, int n)
{
	if (!ret && n == 0)
	{
		ft_putstr("\033[31m");
		ft_putstr("sh1: command not found: ");
		ft_putendl(bin);
		ft_putstr("\033[0m");
	}
}

char	*searchbin(char *paths, char **tab, int n)
{
	int		i;
	char	*tmp;
	DIR		*dir;
	char	*ret;

	ret = NULL;
	i = 0;
	if (tab[0][0] && tab[0][1] && tab[0][0] == '.' && tab[0][1] == '/')
		ret = localbin(tab[0]);
	else
	{
		while (paths[i] && paths[i] != ':')
			i++;
		tmp = ft_strndup(paths, i);
		dir = ft_dir(tmp, 0);
		ret = ft_readdir(dir, tab[0], tmp, 0);
		if (tmp)
			free (tmp);
		ft_dir(dir, 1);
		if (ret == NULL && paths[i + 1])
			ret = searchbin(&paths[i + 1], tab, n++);
	}
	ft_nobin(tab[0], ret, n);
	return (ret);
}

char	*ft_calcprompt(char *prompt, char *home)
{
	int i;

	i = 0;
	if (prompt)
	{
		while (prompt[i] == home[i])
			i++;
	}
	return (&prompt[i]);
}

int		ft_putprompt(char **ev)
{
	char	*pwd;
	char	*home;
	char	*prompt;

	pwd = ft_getenv(ev, "PWD=", 0);
	home = ft_getenv(ev, "HOME=", 0);
	ft_putstr("\033[33m");
	prompt = ft_calcprompt(ft_strstr(pwd, home), home);
	if (prompt)
	{
		ft_putchar('~');
		ft_putstr(prompt);
	}
	else
		ft_putstr(pwd);
	ft_putstr("\033[32m");
	ft_putstr(" $> ");
	ft_putstr("\033[0m");
	return (0);
}

void	ft_clear(void)
{
	ft_putstr("\e[1;1H\e[2J");
}

void	ft_rewrite_path(char **ev, char *pwd)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	buf = NULL;
	while (ev[i] && buf == NULL)
		buf = ft_strnstr(ev[i++], "OLDPWD=", ft_strlen("OLDPWD="));
	if (buf)
		free(buf);
	j = 0;
	buf = NULL;
	while (ev[j] && buf == NULL)
		buf = ft_strnstr(ev[j++], "PWD=", ft_strlen("PWD="));
	if (buf)
	{
		ev[i] = ft_strjoin("OLDPWD=", &buf[ft_strlen("PWD=")]);
		free(buf);
		ev[j] = pwd;
	}
}

void	cderror(char **av, int error)
{
	ft_putstr_fd("\033[31m", 2);
	if (error == 0)
		ft_putstr_fd("cd: No such file or directory: ", 2);
	if (error == 1)
		ft_putendl_fd("cd: Too many arguments", 2);
	if (error == 2)
		ft_putstr_fd("cd: Not a directory: ", 2);
	if (error == 3)
		ft_putstr_fd("cd: Permission denied: ", 2);
	if (error == 0 || error == 2 || error == 3)
		ft_putendl_fd(av[0], 2);
	ft_putstr_fd("\033[0m", 2);
}

int		ft_chdir(char *path)
{
	struct stat 	buf;
	int 			ret;

	ret = -1;
	if (lstat(path, &buf) == -1)
		cderror(&path, 0);
	else if (!S_ISDIR(buf.st_mode) && !S_ISLNK(buf.st_mode))
		cderror(&path, 2);
	else if (!(buf.st_mode & S_IXUSR) && !(buf.st_mode & S_IXGRP) && !(buf.st_mode & S_IXOTH))
		cderror(&path, 3);
	else
		if ((ret = chdir(path)) == -1)
			cderror(&path, 2);
	return (ret);
}

void	cd2args(char **av, char **ev)
{
	(void)av;
	(void)ev;
}

void	cd1arg(char *path, char **ev)
{
	static char current[1024];
	static char prev[1024];
	char 		*pwd;
	int 		ret;

	ret = -1;
	if (!ft_strcmp(path, "-")&& *prev)
	{
		ft_bzero(current, 1024), getcwd(current, 1024);
		ret = ft_chdir(prev);
		ft_memcpy(prev, current, 1024);
	}
	else
	{
		ft_bzero(prev, 1024), getcwd(prev, 1024);
		ft_chdir(path);
	}
	ft_bzero(current, 1024), getcwd(current, 1024);
	if (ret == 0)
	{
		pwd = ft_strjoin("PWD=", current);
		ft_rewrite_path(ev, pwd);
	}
}

void	ft_cd(char **av, char **ev)
{
	char 	*home;
	size_t 	len;

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
		if ((home = ft_getenv(ev, "HOME=", 0)))
			cd1arg(home, ev);
	}
}


void	ft_env(char ***ev, char **av)
{
	int i;

	i = 0;
	if (av[1])
	{
	}
	while (ev[0][i])
		ft_putendl(ev[0][i++]);
}

void	ft_exit(char **av, char **ev, int ret)
{
	ft_strdel(av);
	ft_strdel(ev);
	ft_putendl("\033[31m*** sh1 closed ***\033[0m");
	exit(ret);
}

int		checkndobltn(char ***ev, char **av)
{
	int ret;

	ret = 0;
	if (av[0])
	{
		if (ft_strcmp(av[0], "cd") == 0)
			ft_cd(av, *ev), ret = 1;
		if (ft_strcmp(av[0], "env") == 0)
			ft_env(ev, av), ret = 1;
		if (ft_strcmp(av[0], "exit") == 0)
			ft_exit(av, *ev, 0), ret = 1;
	}
	return (ret);
}

int		exebin(char *path, char **av, char **ev)
{
	int		ret;
	pid_t	father;

	father = fork();
	ret = 0;
	if (father == 0)
	{
		ret = execve(path, av, ev);
		ft_exit(av, ev, ret);
	}
	else
		wait(NULL);
	return (ret);
}

int		docmd(char ***ev)
{
	char	*buf;
	char	**buf2;
	int		ret;
	char	*binpath;

	ret = 0;
	get_next_line(0, &buf);
	buf2 = ft_strsplit(buf, ' ');
	free(buf);
	if (buf2 && buf2[0] && checkndobltn(ev, buf2) == 1)
		ret = 1;
	else if (buf2 && buf2[0] && (buf = ft_getenv(*ev, "PATH=", 0)))
	{
		if ((binpath = searchbin(buf, buf2, 0)))
			ret = exebin(binpath, buf2, *ev);
		if (binpath)
			free(binpath);
	}
	if(buf2)
		ft_strdel(buf2);
	return (ret);
}

char	**ft_evcpy(char **tab)
{
	char	**ev;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	ev = (char **)ft_memalloc(sizeof(char *) * i + 1);
	i = 0;
	while (tab[i])
	{
		ev[i] = ft_strdup(tab[i]);
		i++;
	}
	ev[i] = '\0';
	return (ev);
}

int		main(int ac, char **av, char **ev)
{
	(void)av;
	(void)ac;
	ft_clear();
	ev = ft_evcpy(ev);
	while (1)
	{
		ft_putprompt(ev);
		docmd(&ev);
	}
	ft_strdel(ev);
	return (0);
}
