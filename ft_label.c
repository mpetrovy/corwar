/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <rsavchak@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:18:59 by rsavchak          #+#    #+#             */
/*   Updated: 2018/11/28 18:19:00 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		ft_find_label(t_form *assm, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != ':' && line[i] != '#' && line[i] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, line[i]))
			i++;
		else
			return (0);
	}
	if (line[i] == ':')
	{
		assm->is_l = 1;
		return (i + 1);
	}
	return (0);
}

void	ft_is_l(t_form *assm, char *line, int *i, char *labtmp)
{
	if (assm->is_l == 1)
	{
		labtmp = ft_label_valid(assm, i, line);
		ft_add_label(assm, labtmp);
	}
}

void	ft_add_label(t_form *assm, char *labtmp)
{
	t_l *ptr;

	ptr = NULL;
	if (!assm->labels)
		assm->labels = ft_memalloc(sizeof(t_l));
	if (assm->labels && *assm->labels)
	{
		ptr = *assm->labels;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = ft_memalloc(sizeof(t_l));
		ptr->next->lab = ft_strdup(labtmp);
	}
	else
	{
		*assm->labels = ft_memalloc(sizeof(t_l));
		(*assm->labels)->lab = ft_strdup(labtmp);
		(*assm->labels)->next = ptr;
	}
}

void	ft_label_cpy(t_form *assm, t_op *ptr)
{
	t_l *tmp;
	t_l *start;

	if (!ptr->label)
	{
		ptr->label = ft_memalloc(sizeof(t_l));
		*ptr->label = NULL;
	}
	tmp = *assm->labels;
	while (tmp != NULL)
	{
		start = ft_memalloc(sizeof(t_l));
		if (tmp->lab)
		{
			start->lab = ft_strdup(tmp->lab);
			start->next = (*ptr->label);
			*ptr->label = start;
			ft_strdel(&tmp->lab);
			free(tmp);
		}
		tmp = tmp->next;
	}
	*assm->labels = NULL;
}

char	*ft_label_valid(t_form *assm, int *i, char *line)
{
	int		k;
	char	*lab;
	int		j;

	assm->hash = 0;
	while (line[*i] == ' ' || line[*i] == '\t')
		*i = *i + 1;
	k = *i;
	while (line[*i] != ':')
		*i = *i + 1;
	*i = *i + 1;
	if (ft_find_command(assm, line) == 17)
	{
		j = *i;
		while (line[j] != '\0')
		{
			if (line[j] == '#')
				assm->hash = 1;
			if ((line[j] != ' ' && line[j] != '\t') && assm->hash == 0)
				ft_error("label");
			j++;
		}
	}
	lab = ft_strsub(line, k, *i - k - 1);
	return (lab);
}
