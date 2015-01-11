/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 14:51:25 by bbecker           #+#    #+#             */
/*   Updated: 2015/01/05 14:52:04 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <unistd.h>
# include "libft.h"
# define BUFF 20

typedef struct	s_lst
{
	char			*buf;
	int				fd;
	struct s_lst	*next;
}				t_lst;
int				get_next_line(int const fd, char **line);

#endif
