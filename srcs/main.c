/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/04 15:01:50 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/17 15:51:29 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	ev = cloneenv(ev);
	signal(SIGINT, ft_signal_handler);
	ft_docmd(&ev);
	return (0);
}
