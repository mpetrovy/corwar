/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <rsavchak@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:12:37 by rsavchak          #+#    #+#             */
/*   Updated: 2018/11/28 18:12:38 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

char		*ft_get_name(t_form *assm, char *line, int k)
{
	assm->i = 0;
	while (line[assm->i] == ' ' || line[assm->i] == '\t')
		assm->i = ft_check_space(line, assm->is_n, assm, "name");
	if (ft_strncmp(&line[assm->i], ".name", 5) != 0)
		ft_error("name");
	assm->i = assm->i + 5;
	while (line[assm->i] != '"')
		assm->i = ft_check_space(line, assm->is_n, assm, "name");
	k = assm->i;
	assm->i++;
	while (line[assm->i] != '"' && line[assm->i] != '\0')
		assm->i++;
	if (line[assm->i] == '"')
		assm->name = ft_strsub(line, k + 1, assm->i - k - 1);
	else
		line = ft_name_next(assm, line, k + 1);
	assm->is_n++;
	if (ft_strlen(assm->name) > 128)
		ft_error("name");
	assm->i++;
	while (line[assm->i] != '\0')
		assm->i = ft_check_space(line, assm->is_n, assm, "name");
	assm->hash = 0;
	return (line);
}

char		*ft_name_next(t_form *assm, char *line, int k)
{
	char	*str;
	int		l;

	l = 0;
	assm->i = 0;
	str = ft_strsub(line, k, ft_strlen(line) - k);
	ft_strdel(&line);
	if (!(get_next_line(assm->fd, &line)))
		ft_error("name");
	while (ft_strchr(line, '"') == 0)
	{
		str = ft_strjoin(str, line);
		ft_strdel(&line);
		if (!(get_next_line(assm->fd, &line)))
			ft_error("name");
	}
	while (line[assm->i] != '"')
		assm->i++;
	str = ft_strjoin(str, line);
	while (str[l] != '"')
		l++;
	assm->name = ft_strsub(str, 0, l);
	ft_strdel(&str);
	return (line);
}

char		*ft_get_comment(t_form *assm, char *line, int k)
{
	assm->i = 0;
	while (line[assm->i] == ' ' || line[assm->i] == '\t')
		assm->i = ft_check_space(line, assm->is_n, assm, "comment");
	if (ft_strncmp(&line[assm->i], ".comment", 8) != 0)
		ft_error("comment");
	assm->i = assm->i + 8;
	while (line[assm->i] != '"')
		assm->i = ft_check_space(line, assm->is_c, assm, "comment");
	k = assm->i;
	assm->i++;
	while (line[assm->i] != '"' && line[assm->i] != '\0')
		assm->i++;
	if (line[assm->i] == '"')
		assm->comment = ft_strsub(line, k + 1, assm->i - k - 1);
	else
		line = ft_comment_next(assm, line, k + 1);
	assm->is_c++;
	if (ft_strlen(assm->comment) > 2048)
		ft_error("comment");
	assm->i++;
	while (line[assm->i] != '\0')
		assm->i = ft_check_space(line, assm->is_n, assm, "comment");
	assm->hash = 0;
	return (line);
}

char		*ft_comment_next(t_form *assm, char *line, int k)
{
	char	*str;
	int		l;

	l = 0;
	assm->i = 0;
	str = ft_strsub(line, k, ft_strlen(line) - k);
	ft_strdel(&line);
	if (!(get_next_line(assm->fd, &line)))
		ft_error("comment");
	while (ft_strchr(line, '"') == 0)
	{
		str = ft_strjoin(str, line);
		ft_strdel(&line);
		if (!(get_next_line(assm->fd, &line)))
			ft_error("comment");
	}
	while (line[assm->i] != '"')
		assm->i++;
	str = ft_strjoin(str, line);
	while (str[l] != '"')
		l++;
	assm->comment = ft_strsub(str, 0, l);
	ft_strdel(&str);
	return (line);
}
