/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/08 15:16:28 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/08 18:29:27 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

static char	*ft_findbin(char **ev, char **av)
{
	int i;
	int j;
	int x;

	i = ft_findenv(ev, "PATH=");
	if (ev[i])
		ft_error(1);
	j = 0;
	x = 0;
	while (x == 0 && ev[i] && ev[j])
	{
		while ()
	}
}

int			ft_execve(char **trueenv, char **av, char **ev)
{

}