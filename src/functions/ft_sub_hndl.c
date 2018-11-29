/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_hndl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:21:56 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 21:21:57 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_flag_sub_show(t_env *e, t_carr *car, t_registers *reg)
{
	if ((e->flag_num & 4) == 4)
	{
		ft_printf("P%5d | sub ", car->car_index);
		ft_printf("r%d r%d r%d\n", reg->reg1, reg->reg2, reg->reg3);
	}
}

void		ft_sub_hndl(t_env *e, t_carr *car)
{
	unsigned int	value;
	int				pos;
	t_registers		reg;
	t_get			f[4];

	ft_set_f(f);
	pos = ft_check_pos(car->cur_pos + 2);
	reg.reg1 = e->fild[pos];
	reg.reg2 = e->fild[ft_check_pos(pos + 1)];
	reg.reg3 = e->fild[ft_check_pos(pos + 2)];
	if (reg.reg1 == 0 || reg.reg1 > REG_NUMBER || reg.reg2 == 0 ||
		reg.reg2 > REG_NUMBER || reg.reg3 == 0 || reg.reg3 > REG_NUMBER)
	{
		ft_check_codage(e, car, &car->i, &car->cod);
		car->cur_pos = ft_check_pos(car->cur_pos + 2 + car->ofset);
	}
	else
	{
		value = f[car->args[0]](e, car, &pos) - f[car->args[1]](e, car, &pos);
		car->carry = ((value == 0) ? (1) : (0));
		car->reg[reg.reg3] = value;
		ft_flag_sub_show(e, car, &reg);
		ft_adv_show(e, car, pos + 1 - car->cur_pos);
		car->cur_pos = ft_check_pos(pos + 1);
	}
}
