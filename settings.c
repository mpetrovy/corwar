/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <rsavchak@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:24:46 by rsavchak          #+#    #+#             */
/*   Updated: 2018/11/28 18:24:46 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	ft_size(t_form *assm)
{
	t_op	*ptr;
	int		size;

	size = 0;
	ptr = *assm->com;
	while (ptr != NULL)
	{
		size = size + ptr->bytes;
		ptr = ptr->next;
	}
	ft_write_bit(assm, size, 4, 4);
}

void	ft_set_label(t_form *assm)
{
	t_op	*ptr;
	int		i;
	int		number;

	number = 0;
	ptr = *assm->com;
	while (ptr != NULL)
	{
		i = 0;
		while (ptr->arg[i].type && i <= 2)
		{
			if (ptr->arg[i].labe != NULL)
				ft_label_in_list(assm, ptr, ptr->arg[i].labe, number);
			i++;
		}
		number = number + ptr->bytes;
		ptr = ptr->next;
	}
}

void	ft_label_in_list(t_form *assm, t_op *ptr, char *str, int number)
{
	t_op	*tmp;
	t_l		*node;

	node = NULL;
	assm->check = 0;
	tmp = *assm->com;
	assm->nbr_bytes = 0;
	while (tmp != NULL)
	{
		ft_check_label(tmp, node, assm, str);
		if (assm->check == 1)
			break ;
		assm->nbr_bytes = assm->nbr_bytes + tmp->bytes;
		tmp = tmp->next;
	}
	if (assm->check == 0)
		assm->check = ft_check_label_end(assm, str);
	ft_check_label_code(number, tmp, ptr, assm);
}

void	ft_check_label(t_op *tmp, t_l *node, t_form *assm, char *str)
{
	if (tmp->label)
	{
		node = *tmp->label;
		while (node != NULL)
		{
			if (node->lab != NULL)
				if (ft_strcmp(str, node->lab) == 0)
				{
					assm->check = 1;
					break ;
				}
			node = node->next;
		}
	}
}

void	ft_check_label_code(int number, t_op *tmp, t_op *ptr, t_form *assm)
{
	if (tmp != NULL || assm->check == 42)
	{
		if (assm->nbr_bytes > number)
			ptr->lc = (assm->nbr_bytes - number);
		else
			ptr->lc = -1 * (number - assm->nbr_bytes - 1);
	}
	else
		ft_error("no label");
}
