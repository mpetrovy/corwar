/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 22:03:04 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 22:03:05 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		ft_show_for_debug(t_env *e)
{
	int				k;
	int				ch;
	unsigned int	ref;

	ch = 0;
	k = 0;
	ref = 0;
	ft_printf("0x%.4x : ", ref);
	while (k < MEM_SIZE)
	{
		if (ch == 64)
		{
			ft_printf("\n%#.4x : ", ref);
			ch = 0;
		}
		ft_printf("%.2x ", e->fild[k]);
		k++;
		ch++;
		ref++;
	}
	ft_printf("\n");
}

void		ft_set_handlers(t_hndl *func)
{
	func[1] = &ft_live_hndl;
	func[2] = &ft_ld_hndl;
	func[3] = &ft_st_hndl;
	func[4] = &ft_add_hndl;
	func[5] = &ft_sub_hndl;
	func[6] = &ft_and_hndl;
	func[7] = &ft_or_hndl;
	func[8] = &ft_xor_hndl;
	func[9] = &ft_zjump_hndl;
	func[10] = &ft_ldi_hndl;
	func[11] = &ft_sti_hndl;
	func[12] = &ft_fork_hndl;
	func[13] = &ft_lld_hndl;
	func[14] = &ft_lldi_hndl;
	func[15] = &ft_lfork_hndl;
	func[16] = &ft_aff_hndl;
}

static void	ft_check_print(t_env *e, t_carlist *begin)
{
	ft_printf("Process %d hasn't lived for (%d) cycles (CTD %d)\n",
	begin->carr.car_index, begin->carr.cycles, e->cycle_to_die);
}

void		ft_check_killed_carriage(t_env *e)
{
	t_carlist *begin;
	t_carlist *tmp;

	tmp = NULL;
	begin = e->head;
	while (begin)
	{
		if (begin->carr.alive == 1)
		{
			begin->carr.alive = 0;
			tmp = begin;
			begin = begin->next;
		}
		else
		{
			if (tmp)
				tmp->next = begin->next;
			else
				e->head = e->head->next;
			if ((e->flag_num & 8) == 8)
				ft_check_print(e, begin);
			free(begin);
			begin = tmp ? tmp->next : e->head;
		}
	}
}

void		ft_check_cycle(t_env *e, short *live)
{
	ft_check_killed_carriage(e);
	if (e->lives >= NBR_LIVE || e->checks == MAX_CHECKS)
	{
		e->cycle_to_die -= CYCLE_DELTA;
		e->checks = 1;
	}
	else
		e->checks++;
	if (e->cycle_to_die <= 0)
		*live = 0;
	e->lives = 0;
	if ((e->flag_num & 2) == 2)
		ft_printf("Cycle to die is now %d\n", e->cycle_to_die);
}
