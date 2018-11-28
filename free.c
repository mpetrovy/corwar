/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <rsavchak@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:26:48 by rsavchak          #+#    #+#             */
/*   Updated: 2018/11/28 18:26:49 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	ft_free(t_form *assm)
{
	ft_strdel(&assm->name);
	ft_strdel(&assm->comment);
	free_comlist(*assm->com);
}

void	free_comlist(t_op *head)
{
	t_op	*ptr;
	t_op	*i;
	int		j;

	if ((ptr = head) == NULL)
		return ;
	while (ptr != NULL)
	{
		i = ptr;
		ptr = ptr->next;
		ft_strdel(&i->name);
		j = 0;
		while (&i->arg[j] && j <= 2)
		{
			ft_strdel(&i->arg[j].labe);
			ft_strdel(&i->arg[j].bin);
			j++;
		}
		if (i->label && *i->label)
			ft_free_labelist(*i->label);
		free(i);
	}
}

void	ft_free_labelist(t_l *head)
{
	t_l	*ptr;
	t_l	*i;

	if ((ptr = head) == NULL)
		return ;
	while (ptr != NULL)
	{
		i = ptr;
		ptr = ptr->next;
		ft_strdel(&i->lab);
		free(i);
	}
}

void	ft_error(char *param)
{
	ft_putstr("bad ");
	ft_putendl(param);
	exit(0);
}
