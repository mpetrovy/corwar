/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork_hndl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:20:54 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 21:20:55 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_copy(unsigned int *dst, unsigned int *cp)
{
	int i;

	i = 0;
	while (i < REG_NUMBER)
	{
		dst[i] = cp[i];
		i++;
	}
}

static void	ft_flag_lfork_show(t_env *e, t_carr *car, int value)
{
	if ((e->flag_num & 4) == 4)
	{
		ft_printf("P%5d | lfork %d (%d)\n", car->car_index, value,
		ft_check_pos(car->cur_pos + (value % IDX_MOD)));
	}
}

static void	ft_add_cursor(t_env *e, t_carr *car, int pos)
{
	t_carlist	*lst;
	t_carlist	*tmp;

	tmp = e->head;
	if (!(lst = (t_carlist*)malloc(sizeof(t_carlist))))
		return ;
	lst->carr.cur_pos = ft_check_pos(car->cur_pos + pos);
	//printf("lfork  new carpos %d\n", lst->carr.cur_pos);
	lst->carr.player = car->player;
	lst->carr.car_index = e->carriage_index;
	lst->carr.carry = car->carry;
	ft_copy(lst->carr.reg, car->reg);
	lst->carr.alive = car->alive;
	lst->carr.command = 0;
	lst->carr.cycles = 0;
	lst->next = tmp;
	e->head = lst;
	e->carriage_index++;
}

void		ft_lfork_hndl(t_env *e, t_carr *car)
{
	short			value;
	unsigned int	step;

	// printf("LFORK NOW\n");
	step = 3;
	value = (short)ft_get_value(e, car->cur_pos + 1, 2);
	ft_add_cursor(e, car, value);
	ft_flag_lfork_show(e, car, value);
	ft_adv_show(e, car, step);
	car->cur_pos = ft_check_pos(car->cur_pos + step);
	//printf("lfork carpos %d\n", car->cur_pos);
}
