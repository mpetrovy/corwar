/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:16:50 by daalexan          #+#    #+#             */
/*   Updated: 2018/02/11 12:16:54 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_read	*ft_mk_list(t_read *list, const int fd)
{
	t_read	*begin;
	t_read	*prev;

	prev = NULL;
	begin = list;
	while (list && list->fd != fd)
	{
		prev = list;
		list = list->next;
	}
	if (!list)
	{
		if (!(list = ft_memalloc(sizeof(t_read))))
			return (NULL);
		list->fd = fd;
	}
	if (prev)
		prev->next = list->next;
	if (list != begin)
		list->next = begin;
	return (list);
}

static int		ft_delete(t_read *list, char **line, char *buf)
{
	ft_strdel(&buf);
	if (**line)
		return (OK);
	list->fd = 0;
	return (END);
}

static int		mk_endl(char *s1)
{
	int	len;

	len = 0;
	while (s1[len] != '\n')
		len++;
	return (len);
}

static int		ft_read(char *buf, t_read *list, char **line)
{
	char	*arr;
	char	*help;

	arr = ft_strdup(*line);
	ft_strdel(line);
	if (ft_strrchr(buf, '\n'))
	{
		help = ft_strsub(buf, 0, mk_endl(buf));
		*line = ft_strjoin(arr, help);
		ft_strdel(&help);
		list->data = ft_strsub(buf, (mk_endl(buf) + 1),\
		ft_strlen(buf) - mk_endl(buf));
		ft_strdel(&buf);
		ft_strdel(&arr);
		return (OK);
	}
	*line = ft_strjoin(arr, buf);
	ft_strclr(buf);
	ft_strdel(&arr);
	return (END);
}

int				get_next_line(const int fd, char **line)
{
	static t_read	*list;
	char			*buf;
	int				res;

	res = 0;
	if (!line || BUFF_SIZE <= 0 || fd < 0 || read(fd, 0, 0)
		|| !(*line = ft_strnew(0))
		|| !(list = ft_mk_list(list, fd)))
		return (ERROR);
	if (list->data && ft_read(list->data, list, line))
		return (OK);
	ft_strdel(&list->data);
	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (ERROR);
	while ((res = read(fd, buf, BUFF_SIZE)))
	{
		buf[res] = '\0';
		if (ft_read(buf, list, line))
			return (OK);
		if (res < BUFF_SIZE)
			break ;
	}
	if (ft_delete(list, line, buf))
		return (OK);
	return (END);
}
