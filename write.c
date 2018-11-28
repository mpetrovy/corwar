/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <rsavchak@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:23:15 by rsavchak          #+#    #+#             */
/*   Updated: 2018/11/28 18:23:16 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	ft_write(t_form *assm, char *fname, unsigned long i)
{
	char			*file;
	char			*z;

	file = NULL;
	ft_set_label(assm);
	file = ft_strsub(fname, 0, ft_strlen(fname) - 2);
	z = file;
	file = ft_strjoin(file, ".cor");
	ft_strdel(&z);
	assm->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	ft_write_bit(assm, COREWAR_EXEC_MAGIC, 4, 4);
	while (assm->name[i] != '\0')
	{
		ft_write_bit(assm, assm->name[i], 1, 1);
		i++;
	}
	i = 0;
	while (i < 132 - ft_strlen(assm->name))
	{
		ft_write_bit(assm, 0, 1, 1);
		i++;
	}
	ft_write_comment(assm);
	ft_write_command(assm, 0);
	ft_strdel(&file);
}

void	ft_write_bit(t_form *assm, int c, int bit, int i)
{
	unsigned char	table[bit];

	while (bit)
	{
		bit--;
		table[bit] = (unsigned char)c;
		c >>= 8;
	}
	while (bit < i)
	{
		write(assm->fd, &table[bit], 1);
		bit++;
	}
}

void	ft_write_command(t_form *a, int i)
{
	t_op	*p;

	p = *a->com;
	while (p != NULL)
	{
		ft_write_bit(a, p->hex, 1, 1);
		if (p->codage == 1)
			ft_write_bit(a, p->cod, 1, 1);
		i = 0;
		while (p->arg[i].type && i <= 2)
		{
			if (p->arg[i].labe != NULL)
			{
				if (p->lc > 0)
					ft_write_bit(a, p->lc, p->arg[i].type, p->arg[i].type);
				else
					ft_write_bit(a, MAX + p->lc, p->arg[i].type, \
					p->arg[i].type);
			}
			else
				ft_write_bit(a, p->arg[i].val, p->arg[i].type, p->arg[i].type);
			i++;
		}
		p = p->next;
	}
}

void	ft_write_comment(t_form *assm)
{
	unsigned long	i;

	i = 0;
	ft_size(assm);
	while (assm->comment[i] != '\0')
	{
		ft_write_bit(assm, assm->comment[i], 1, 1);
		i++;
	}
	i = 0;
	while (i < 2052 - ft_strlen(assm->comment))
	{
		ft_write_bit(assm, 0, 1, 1);
		i++;
	}
}
