/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell1.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/01 14:39:27 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/16 19:28:42 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL1_H
# define FT_MINISHELL1_H

# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>

/*
**	cmd.c
*/

void	ft_docmd(char ***ev);

/*
**	builtinschecker.c
*/

int		ft_builtins(char ***ev, char **av);

/*
**	exit.c
*/

void	ft_exit(char **av);

/*
**	ft_execve.c
*/

int		ft_execve(char **trueenv, char **av, char **ev);

/*
**	utilities.c
*/

void	ft_checknull(void *stuff);
char	**cloneenv(char **ev);
int		ft_findenv(char *var, char **ev, int i);

/*
**	findbin.c
*/

char	*ft_findbin(char **ev, char **av);

/*
**	split.c
*/

char	**ft_split(char const *s);

/*
**	env.c
*/

void	ft_env(char **trueenv, char **av);
int		ft_searchenv(char **ev, int i);

/*
**	setenv.c
*/

int		ft_putenv(char **ev, char *var, int param);
int		ft_setenv(char ***ev, char *var);

/*
**	unsetenv.c
*/

int		ft_unsetenv(char ***ev, char **av);

/*
**	cd.c
*/

void	ft_cd(char **av, char ***ev);

/*
**	realloctab.c
*/

char	**ft_realloctab(char **tab, int what, size_t *i);

/*
**	errors.c
*/

void	ft_error(int err, char *str);
void	cderror(char **av, int error);

#endif
