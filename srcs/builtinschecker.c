/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinschecker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 15:03:36 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/16 19:20:16 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int		ft_builtins(char ***ev, char **av)
{
	int	ret;

	ret = 0;
	(void)ev;
	(void)av;
	if (ft_strcmp(av[0], "env") == 0)
		ft_env(*ev, av), ret = 1;
	else if (ft_strcmp(av[0], "setenv") == 0)
		ft_setenv(ev, av[1]), ret = 1;
	else if (ft_strcmp(av[0], "unsetenv") == 0)
		ft_unsetenv(ev, &av[1]), ret = 1;
	else if (ft_strcmp(av[0], "clear") == 0)
		ft_putstr("\033[1;1H\033[2J"), ret = 1;
	else if (ft_strcmp(av[0], "cd") == 0)
		ft_cd(av, ev), ret = 1;
	else if (ft_strcmp(av[0], "exit") == 0)
		ft_exit(av), ret = 1;
	else if (ft_strcmp(av[0], "quit") == 0)
		ft_exit(av), ret = 1;
	else if (ft_strcmp(av[0], "4") == 0)
		ft_putendl("He he he he"), ret = 1;
	return (ret);
}
