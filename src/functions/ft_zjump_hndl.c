/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjump_hndl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:22:08 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 21:22:09 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_flag_zjump_show(t_env *e, t_carr *car, int step)
{
	if ((e->flag_num & 4) == 4)
	{
		ft_printf("P%5d | zjmp %d ", car->car_index, step);
		(car->carry == 1) ? (ft_printf("OK\n")) : (ft_printf("FAILED\n"));
	}
}

void		ft_zjump_hndl(t_env *e, t_carr *car)
{
	short	position;

	position = ft_get_value(e, car->cur_pos + 1, e->funcs[car->command].label);
	position %= IDX_MOD;
	if (car->carry == 1)
	{
		car->cur_pos = ft_check_pos(position + car->cur_pos);
		ft_flag_zjump_show(e, car, position);
	}
	else
	{
		ft_flag_zjump_show(e, car, position);
		car->cur_pos = ft_check_pos(car->cur_pos + 3);
	}
}
