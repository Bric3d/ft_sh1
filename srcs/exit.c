/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/14 13:28:40 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/16 13:38:13 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void	ft_exit(char **av)
{
	int ret;

	ret = 0;
	if (av && av[1])
		ret = ft_atoi(av[1]);
	ft_putstr("exit with value ");
	ft_putnbr(ret);
	ft_putchar('\n');
	exit(ret);
}
