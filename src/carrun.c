/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carrun.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:36:06 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/07 18:36:07 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_update(t_env *e)
{
	t_carlist *begin;

	begin = e->head;
	while (begin)
	{
		if (begin->carr.cur_pos == MEM_SIZE)
			begin->carr.cur_pos = 0;
		//printf("%x pos = %u player = %d\n", e->fild[begin->carr.cur_pos], begin->carr.cur_pos, begin->carr.plr_num);
		begin->carr.cur_pos++;
		begin = begin->next;
	}
	// e->head = begin;
}

void	ft_carriage_run(t_env *e)
{
	short	live;

	live = 1;
	printf("here\n"); 
	while (live)
	{
		if (e->head->carr.cur_pos == 4096)
			break ;
		ft_update(e);
	}
}
