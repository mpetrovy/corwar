/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or_hndl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:21:21 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 21:21:22 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_flag_or_show(t_env *e, t_carr *car, t_registers *reg)
{
	if ((e->flag_num & 4) == 4)
	{
		ft_printf("P%5d | or %d %d r%d\n", car->car_index,
		reg->reg1, reg->reg2, reg->reg3);
	}
}

void		ft_or_hndl(t_env *e, t_carr *car)
{
	int			value;
	int			pos;
	t_registers reg;
	t_get		f[4];

	ft_set_f(f);
	pos = ft_check_pos(car->cur_pos + 2);
	reg.reg1 = f[car->args[0]](e, car, &pos);
	reg.reg2 = f[car->args[1]](e, car, &pos);
	value = reg.reg1 | reg.reg2;
	reg.reg3 = e->fild[pos];
	if (reg.reg3 > 0 && reg.reg3 <= REG_NUMBER)
	{
		ft_flag_or_show(e, car, &reg);
		car->carry = ((value == 0) ? (1) : (0));
		car->reg[reg.reg3] = value;
		ft_adv_show(e, car, pos + 1 - car->cur_pos);
		car->cur_pos = ft_check_pos(pos + 1);
	}
	else
	{
		ft_check_codage(e, car, &car->i, &car->cod);
		car->cur_pos = ft_check_pos(car->cur_pos + 2 + car->ofset);
	}
}
