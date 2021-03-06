/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 15:16:28 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/17 16:44:23 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static int	ft_binaccess(char **binpath)
{
	int x;

	if (*binpath)
	{
		x = access(*binpath, X_OK);
		if (x == 0)
			return (0);
		ft_error(2, *binpath);
		return (-2);
		free(*binpath);
		*binpath = NULL;
	}
	return (-1);
}

int			ft_execve(char **trueenv, char **av, char **ev)
{
	char	*binpath;
	pid_t	father;
	int		ret;

	if (!av || !av[0])
		return (0);
	ret = 0;
	binpath = ft_findbin(trueenv, av);
	if ((ret = ft_binaccess(&binpath)) == 0)
	{
		father = fork();
		if (father == 0)
		{
			signal(SIGINT, SIG_DFL);
			ret = execve(binpath, av, ev);
			exit(ret);
		}
		else
			wait(NULL), ret = 1;
	}
	else if (ret == -1)
		ft_error(3, av[0]);
	if (binpath != NULL)
		free(binpath);
	return (ret);
}
