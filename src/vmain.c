/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 18:18:12 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/04 18:19:20 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_memclr(t_env *e)
{
	int			j;
	t_carlist	*begin;
	t_carlist	*tmp;

	begin = e->head;
	while (begin)
	{
		tmp = begin;
		begin = begin->next;
		free(tmp);
	}
	j = 0;
	while (j < e->plr_numb)
	{
		free(e->plrs[j].code);
		j++;
	}
}

int		main(int ac, char **av)
{
	t_env	e;

	if (ac < 2)
		ft_printf("Usage: [flags] [files] ...\n");
	else
	{
		e.dump = -1;
		ft_parse_input(&e, ac, av);
		ft_read_cor(&e, ac);
		ft_fill_env(&e, 0, 0);
		ft_init_carriage(&e);
		ft_carriage_run(&e);
	}
	ft_memclr(&e);
	return (0);
}
