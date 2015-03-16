/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 17:53:01 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/16 19:21:18 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void	ft_error(int err, char *str)
{
	ft_putstr_fd("\033[31m", 2);
	if (err == 1)
		ft_putendl_fd("sh1: Please set a PATH value using setenv", 2);
	if (err == 2 || err == 3 || err == 4)
	{
		ft_putstr_fd("sh1: ", 2);
		if (err == 2)
			ft_putstr_fd("permission denied: ", 2);
		else if (err == 3)
			ft_putstr_fd("command not found: ", 2);
		else if (err == 4)
			ft_putstr_fd("This environment variable does not exist: ", 2);
		ft_putendl_fd(str, 2);
	}
	if (err == 5)
		ft_putendl_fd("sh1: Something went wrong with malloc.", 2);
	ft_putstr_fd("\033[0m", 2);
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
	if (error == 4)
		ft_putendl_fd("cd: There is no set HOME variable", 2);
	if (error == 5)
		ft_putendl_fd("cd: You need to use cd at least once for this to work.",
		2);
	if (error == 0 || error == 2 || error == 3)
		ft_putendl_fd(av[0], 2);
	ft_putstr_fd("\033[0m", 2);
}
