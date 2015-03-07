/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell1.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/01 14:39:27 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/07 17:15:07 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL1
# define FT_MINISHELL1

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

void	ft_docmd(char **ev);

/*
**	builtinschecker.c
*/

int		ft_builtins(char **ev, char **av);

/*
**	utilities.c
*/

void	ft_checknull(void *stuff);
char	**cloneenv(char **ev);

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

int		ft_setenv(char **ev, char *var, int param);

#endif