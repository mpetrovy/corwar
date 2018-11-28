/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <rsavchak@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:26:11 by rsavchak          #+#    #+#             */
/*   Updated: 2018/11/28 18:26:12 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		ft_check_label_end(t_form *assm, char *str)
{
	t_l *ptr;

	if (assm->labels)
	{
		if ((*assm->labels)->lab != NULL)
		{
			ptr = *assm->labels;
			while (ptr != NULL)
			{
				if (ft_strcmp(str, ptr->lab) == 0)
					return (42);
				ptr = ptr->next;
			}
		}
	}
	return (0);
}

int		ft_space_line(char *line)
{
	int i;
	int hash;

	hash = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '#')
			hash = 1;
		if (line[i] != ' ' && line[i] != '\t' && hash == 0)
			return (0);
		i++;
	}
	return (1);
}

int		ft_check_space(char *line, int nc, t_form *assm, char *param)
{
	if (nc == 0)
	{
		if (line[assm->i] != ' ' && line[assm->i] != '\t')
			ft_error(param);
		assm->i++;
	}
	if (nc == 1)
	{
		if (line[assm->i] == '#' || line[assm->i] == ';')
			assm->hash = 1;
		if (line[assm->i] != ' ' && line[assm->i] != '\t' && assm->hash == 0)
			ft_error(param);
		assm->i++;
	}
	return (assm->i);
}

char	**ft_trim(char **argument, int i, char *arg)
{
	while (argument[i])
	{
		arg = ft_strtrim(argument[i]);
		ft_strdel(&argument[i]);
		argument[i] = ft_strdup(arg);
		ft_strdel(&arg);
		i++;
	}
	return (argument);
}
