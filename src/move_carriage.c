/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_carriage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:54:18 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 21:55:17 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_hndl g_func[17];

static int	ft_check_valid(t_env *e, t_carr *car, int arg)
{
	int			i;

	if (e->funcs[car->command].zero_code == 0)
		return (1);
	car->cod.nbr = e->fild[ft_check_pos(car->cur_pos + 1)];
	car->cod.arg = arg;
	i = 0;
	while (i < arg)
	{
		ft_check_argum(e, car, &i, &car->cod);
		i++;
	}

	return ((car->ofset) ? (0) : (1));
}

static void	ft_move_carr(t_env *e, t_carr *car)
{
	if (car->command == 0)
	{
		car->command = e->fild[car->cur_pos];
		car->cycles = e->funcs[car->command].cycles - 1;
		car->ofset = 0;
		car->working = 1;
	}
	if (car->working == 0 && car->cycles == 0)
	{
		if (ft_check_valid(e, car, e->funcs[car->command].args))
			g_func[car->command](e, car);
		else
		{
			ft_adv_show(e, car, car->ofset + 2);
			car->cur_pos = ft_check_pos(car->cur_pos + car->ofset + 2);
			car->ofset = 0;
		}
		car->command = 0;
	}
	else
	{
		car->cycles--;
		if (car->cycles == 0)
			car->working = 0;
	}
}

static void	ft_handle_command(t_env *e, t_carr *car)
{
	if (e->fild[car->cur_pos] >= 1 && e->fild[car->cur_pos] <= 16)
	{
		ft_move_carr(e, car);
	}
	else
		car->cur_pos = ft_check_pos(car->cur_pos + 1);
}

void		ft_update(t_env *e)
{
	t_carlist *begin;

	begin = e->head;
	while (begin)
	{
		// if (begin->carr.cur_pos >= MEM_SIZE)
		// 	begin->carr.cur_pos = ft_check_pos(begin->carr.cur_pos);
		ft_handle_command(e, &begin->carr);
		begin = begin->next;
	}
}

void		ft_carstep(t_env *e, int *cycles)
{
	short	live;
	int		cur_cycle;

	cur_cycle = 1;
	live = 1;
	ft_set_handlers(g_func);
	while (live)
	{
		if (*cycles == e->dump)
			break ;
		if ((e->flag_num & 2) == 2)
			ft_printf("It is now cycle %d\n", *cycles);
		ft_update(e);
		if (cur_cycle == e->cycle_to_die)
		{
			ft_check_cycle(e, &live);
			cur_cycle = 0;
		}
		(*cycles)++;
		cur_cycle++;
	}
}
