/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <rsavchak@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:16:23 by rsavchak          #+#    #+#             */
/*   Updated: 2018/11/28 18:16:25 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		ft_find_command(t_form *assm, char *line)
{
	int i;
	int j;
	int k;

	i = 0;
	j = ft_find_label(assm, line);
	while (i < 16)
	{
		if (ft_strstr(line + j, g_op_tab[i].name))
		{
			while (line[j] == ' ' || line[j] == '\t')
				j++;
			if (line[j] == '#')
				return (17);
			k = j;
			while (line[j] != ' ' && line[j] != '\t')
				j++;
			if (ft_strncmp(line + k, g_op_tab[i].name, j - k) == 0)
				return (i);
			j = k;
		}
		i++;
	}
	return (17);
}

char	*ft_get_command(t_form *assm, char *line, int i, char *labtmp)
{
	ft_is_l(assm, line, &i, labtmp);
	while ((assm->i_cmd = ft_find_command(assm, line)) == 17)
	{
		i = 0;
		ft_strdel(&line);
		if (!(get_next_line(assm->fd, &line)))
		{
			line = NULL;
			assm->is_com = 0;
			break ;
		}
		if (ft_find_label(assm, line) >= 1)
		{
			labtmp = ft_label_valid(assm, &i, line);
			ft_add_label(assm, labtmp);
			ft_strdel(&labtmp);
		}
		else if (ft_find_command(assm, line) == 17 && ft_space_line(line) == 0)
			ft_error("line");
	}
	if (assm->is_com != 0)
		ft_add_command(assm, line, i);
	assm->is_l = 0;
	return (line);
}

int		ft_tabs(t_form *assm, char *str, int i, int *k)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	*k = i;
	while (str[i] != ' ' && str[i] != '\t')
		i++;
	if (!assm->com)
		assm->com = ft_memalloc(sizeof(t_op));
	return (i);
}

void	ft_add_command(t_form *assm, char *line, int i)
{
	int		k;
	t_op	*ptr;

	i = ft_tabs(assm, line, i, &k);
	ptr = NULL;
	if (assm->com && *assm->com)
	{
		ptr = *assm->com;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = ft_memalloc(sizeof(t_op));
		ptr->next->name = ft_strsub(line, k, i - k);
		ft_com_init(ptr->next, assm);
		ft_arguments(ptr->next, line + i, assm->i_cmd);
	}
	else
	{
		*assm->com = ft_memalloc(sizeof(t_op));
		(*assm->com)->name = ft_strsub(line, k, i - k);
		ft_com_init(*assm->com, assm);
		ft_arguments(*assm->com, line + i, assm->i_cmd);
		(*assm->com)->next = ptr;
	}
}

void	ft_com_init(t_op *ptr, t_form *assm)
{
	ptr->argc = g_op_tab[assm->i_cmd].argc;
	ptr->hex = g_op_tab[assm->i_cmd].hex;
	ptr->labelsize = g_op_tab[assm->i_cmd].labelsize;
	ptr->codage = g_op_tab[assm->i_cmd].codage;
	if (assm->is_l == 1)
		ft_label_cpy(assm, ptr);
	else
		ptr->label = NULL;
	assm->is_cmd++;
}
