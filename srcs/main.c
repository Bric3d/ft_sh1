/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/04 15:01:50 by bbecker           #+#    #+#             */
/*   Updated: 2015/01/06 20:25:22 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

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
	if (tab[1])
		free(tab[1]);
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


void	ft_clear(void)
{
	ft_putstr("\e[1;1H\e[2J");
}
/*
void	ft_rewrite_path(char **av, char **ev)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	buf = NULL;
	while (ev[i] && buf == NULL)
		buf = ft_strnstr(ev[i], "OLDPWD=", ft_strlen("OLDPWD="));
	if (buf)
		free(buf), i = j;
	i = 0;
	buf = NULL;
	while (ev[i] && buf == NULL)
		buf = ft_strnstr(ev[i], "PWD=", ft_strlen("PWD="));
	if (buf)
		ev[j] = buf;
	if (ft_strcmp(av[1], "..") == 0 && ft_strcmp(ev[i], "/") != 0)
	{
	}
}
*/
void	cderror(char **av, int error)
{
	ft_putstr("\033[31m");
	if (error == 0)
		ft_putstr("cd: no such file or directory: ");
	if (error == 0)
		ft_putendl(av[1]);
	ft_putstr("\033[0m");
}

void	ft_cd(char **av, char **ev)
{
	DIR		*dir;
	char	*buf;

	buf = NULL;
	dir = ft_dir(ft_getenv(ev, "PWD=", 1), 2);
	if (!(ft_readdir(dir, av[0], NULL, 1)) && !(ft_dir(dir, 3)))
		cderror(av, 0);
	else
	{
		//ft_rewrite_path(av, ev);
		errno = 0;
		if (av[1][0] != '.')
		{
			buf = ft_strjoin("./", av[1]);
			chdir(buf);
			free(buf);
		}
		else
			chdir(av[1]);
	}
	if (errno != 0)
		cderror(av, 1);
}

char	*searchbin(char *paths, char **tab)
{
	int		i;
	char	*tmp;
	DIR		*dir;
	char	*ret;

	ret = NULL;
	i = 0;
	if (tab[0][0] && tab[0][1] && tab[0][0] == '.' && tab[0][1] == '/')
	{
		dir = ft_dir("./", 0);
		ret = ft_readdir(dir, tab[0], "./", 0);
		dir = ft_dir(dir, 1);
	}
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
			ret = searchbin(&paths[i + 1], tab);
	}
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

int		checkndobltn(char **ev, char **av)
{
	if (ft_strcmp(av[1], "cd") == 0)
		ft_cd(av, ev);
	return (0);
}

int		exebin(char *path, char **av, char **ev)
{
	int		ret;
	pid_t	father;

	father = fork();
	ret = 0;
	if (father == 0)
		ret = execve(path, av, ev);
	else
		wait(NULL);
	return (ret);
}

int		docmd(char **ev)
{
	char	*buf;
	char	**buf2;
	int		ret;
	char	*binpath;

	ret = 0;
	get_next_line(0, &buf);
	buf2 = ft_strsplit(buf, ' ');
	free(buf);
	if (checkndobltn(ev, buf2) == 1)
		return (1);
	if (buf2[0] && (buf = ft_getenv(ev, "PATH=", 0)))
	{
		if ((binpath = searchbin(buf, buf2)))
			ret = exebin(binpath, buf2, ev);
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
		docmd(ev);
	}
	ft_strdel(ev);
	return (0);
}
