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

// const int g_cycle[17] = {0, 10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};

//static t_op g_op_tab[17];

void	ft_show_for_debug(t_env *e)
{
	int k = 0;
	int ch = 0;
	
	while (k < MEM_SIZE)
	{
		if (ch == 64)
		{
			ch = 0;
			printf("\n");
		}
		printf("%x ", e->fild[k]);
		k++;
		ch++;
	}
}

void	ft_memclr(t_env *e)
{
	int j;
	t_carlist	*begin;
	t_carlist	*tmp;

	printf("Mem clear\n");//delete
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

void	ft_show_info(t_env *e)
{
	unsigned int i;
	int j = 0;

	while (j < e->plr_numb)
		{
			i = 0;
			printf("data %u\n", e->plrs[j].head.magic);//dele
			printf("name %s\n", e->plrs[j].head.prog_name);
			printf("comment %s\n", e->plrs[j].head.comment);
			while (i < e->plrs[j].head.prog_size)
			{
				printf("%x ", e->plrs[j].code[i]);
				i++;
			}
			j++;
		}
		printf("\n");
}

int main(int ac, char **av)
{
	t_env	e;

	if (ac < 2)
		ft_error(av[0], "Not enough files");
	else
	{
		ft_parse_input(&e, ac, av);
		ft_read_cor(&e, ac);
		//ft_show_info(&e);
		ft_fill_env(&e, 0, 0);
		ft_init_carriage(&e);
		ft_carriage_run(&e);
		//ft_show_for_debug(&e);
	}
	ft_memclr(&e);
	return (0);	
}
