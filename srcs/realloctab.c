/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloctab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/15 16:22:58 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/15 18:04:48 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

/*
**	ft_realoctab : if what = 1, return a tab with one more case than **tab
**	if what = 2, return a tab with one less case.
*/

char	**ft_realloctab(char **tab, int what, size_t *i)
{
	char	**ret;

	ret = NULL;
	*i = ft_tablen(tab);
	if (what == 1)
		ret = ft_memalloc(sizeof(char *) * (*i + 2));
	if (what == 2 && *i > 0)
		ret = ft_memalloc(sizeof(char *) * (*i + 1));
	return (ret);
}
