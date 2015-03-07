/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbecker <bbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/07 11:28:16 by bbecker           #+#    #+#             */
/*   Updated: 2015/03/07 12:46:06 by bbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_join(char *s1, char *s2)
{
	size_t	b;
	size_t	c;
	char	*data;
	size_t	d;

	if (!s1 || !s2)
		return (NULL);
	b = ft_strlen(s1);
	c = ft_strlen(s2);
	data = (char *)ft_memalloc(sizeof(char *) * (b + c + 1));
	d = 0;
	while (s1 && d < b)
	{
		data[d] = s1[d];
		d++;
	}
	d = 0;
	while (s2 && d < c)
	{
		data[d + b] = s2[d];
		d++;
	}
	data[b + c + 1] = '\0';
	free(s1);
	return (data);
}


t_lst *get_buff_fd(int fd, t_lst *list)
{
	while (list)
	{
		if (list->fd == fd)
			return (list);
		list = list->next;
	}
	if ((list = (t_lst*)malloc(sizeof(t_lst))) == NULL)
		return (NULL);
	if ((list->buf = (char*)ft_memalloc(BUFF_SIZE + 1)) == NULL)
		return (NULL);
	list->fd = fd;
	return (list);

}
static int	ft_gnl_cut(int fd, char **line, char **buf, char *pos)
{
	int	ret;
	*line = ft_strdup(*buf);
	while (!pos)
	{
		if ((ret = read(fd, *buf, BUFF_SIZE)) < 0)
			return (-1);
		if ((pos = ft_strchr(*buf, '\n')) == NULL && !ret)
			return ((*buf)[0] = 0);
		else if (pos)
		{
			(*buf)[ret] = ret ? 0 : (*buf)[ret];
			pos[0] = 0;
			*line = ft_join(*line, *buf);
			ft_strcpy(*buf, pos + 1);
		}
		else
		{
			(*buf)[ret] = ret ? 0 : (*buf)[ret];
			*line = ft_join(*line, *buf);
			(*buf)[0] = 0;
		}
	}
	return (*line ? 1 : -1);
}

int	get_next_line(int const fd, char **line)
{
	static t_lst *begin_list;
	t_lst *list;
	char	*pos;
	int	ret;
	if (!begin_list)
		if ((begin_list = get_buff_fd(fd, begin_list)) == NULL)
			return (-1);
	if ((list = get_buff_fd(fd, begin_list)) == NULL)
		return (-1);
	pos = ft_strchr(list->buf, '\n');
	if (pos)
	{
		*pos = 0;
		*line = ft_strdup(list->buf);
		ft_strcpy(list->buf, pos + 1);
		return (*line ? 1 : -1);
	}
	else
		ret = ft_gnl_cut(fd, line, &list->buf, NULL);
	if (ret == -1)
		return (-1);
	return (ret ? 1 : ft_strlen(*line) != 0);
}
