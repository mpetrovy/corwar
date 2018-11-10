/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 19:26:48 by rsavchak          #+#    #+#             */
/*   Updated: 2018/05/24 16:21:23 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_buffer(int fd, char **temp, int *ret)
{
	char	*bufer;
	char	*string;

	bufer = ft_memalloc(BUFF_SIZE + 1);
	*ret = read(fd, bufer, BUFF_SIZE);
	if (*ret < 0)
		return ;
	if (*ret == 0)
	{
		if (bufer)
			ft_strdel(&bufer);
		if (*temp[0] != '\0')
			*temp = ft_strncat(*temp, "\n", 1);
		return ;
	}
	if (!(string = ft_strjoin(*temp, bufer)))
	{
		*ret = -1;
		return ;
	}
	ft_strdel(temp);
	*temp = string;
	ft_strdel(&bufer);
}

int		get_next_line(int fd, char **line)
{
	static t_old	old;
	char			*nextl;
	int				ret;

	if (fd < 0 || line == NULL || read(fd, 0, 0) < 0 || BUFF_SIZE <= 0)
		return (-1);
	if (old.fd != fd || old.temp == NULL)
		old.temp = ft_memalloc(1);
	nextl = ft_strchr(old.temp, '\n');
	while (nextl == NULL)
	{
		ft_buffer(fd, &old.temp, &ret);
		if (ret < 0)
			return (-1);
		if (ret == 0 && old.temp[0] == '\0')
			return (0);
		nextl = ft_strchr(old.temp, '\n');
	}
	if (!(*line = ft_strsub(old.temp, 0, nextl - old.temp)))
		return (-1);
	nextl = ft_strdup(nextl + 1);
	free(old.temp);
	old.temp = nextl;
	old.fd = fd;
	return (1);
}
