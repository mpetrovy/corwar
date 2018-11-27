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
	int j;
	t_carlist	*begin;
	t_carlist	*tmp;

	//printf("Mem clear\n");//delete
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

// void	ft_show_info(t_env *e)
// {
// 	unsigned int i;
// 	int j = 0;

// 	while (j < e->plr_numb)
// 		{
// 			i = 0;
// 			printf("data %u\n", e->plrs[j].head.magic);//dele
// 			printf("name %s\n", e->plrs[j].head.prog_name);
// 			printf("comment %s\n", e->plrs[j].head.comment);
// 			while (i < e->plrs[j].head.prog_size)
// 			{
// 				printf("%x ", e->plrs[j].code[i]);
// 				i++;
// 			}
// 			j++;
// 		}
// 		printf("\n");
// }

int main(int ac, char **av)
{
	t_env	e;

	if (ac < 2)
		ft_error(av[0], "Not enough files");
	else
	{
		e.dump = -1;
		ft_parse_input(&e, ac, av);
		ft_read_cor(&e, ac);
		//ft_show_info(&e);
		ft_fill_env(&e, 0, 0);
		ft_init_carriage(&e);
		ft_carriage_run(&e);
		//ft_show_for_debug(&e);
	}
	ft_memclr(&e);
	// system("leaks corewar");
	return (0);	
}
