/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sti_hndl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:21:50 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 21:21:51 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_flag_sti_show(t_env *e, t_carr *car, int reg, t_intstruct *val)
{
	if ((e->flag_num & 4) == 4)
	{
		ft_printf("P%5d | sti r%d %d %d\n", car->car_index, reg,
		val->reg2, val->reg1);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			val->reg2, val->reg1, val->reg1 + val->reg2, val->reg3);
	}
}

static void	ft_ind_sec(t_env *e, t_carr *car)
{
	t_intstruct	val;
	int			reg;
	int			i;

	reg = e->fild[ft_check_pos(car->cur_pos + 2)];
	val.reg1 = car->cur_pos + 3;
	val.reg2 = ft_get_value(e, val.reg1, e->funcs[car->command].label);
	val.reg2 = ft_get_value(e, (val.reg2 % IDX_MOD), 4);
	val.reg1 += e->funcs[car->command].label;
	val.reg3 = ft_get_value(e, val.reg1, e->funcs[car->command].label);
	val.reg3 = car->cur_pos + (val.reg2 + val.reg3) % IDX_MOD;
	ft_flag_sti_show(e, car, reg, &val);
	i = -1;
	while (++i < 4)
		e->fild[val.reg3 + i] = (car->reg[reg] >> (8 * (3 - i)) & 255);
	ft_adv_show(e, car, val.reg1 + 2 - car->cur_pos);
	car->cur_pos = ft_check_pos(val.reg1 + 2);
}

static void	ft_sti(t_env *e, t_carr *car)
{
	t_intstruct	val;
	int			reg;
	int			i;
	int			reg1;

	reg = e->fild[ft_check_pos(car->cur_pos + 2)];
	reg1 = ft_check_pos(car->cur_pos + 3);
	val.reg2 = (short)ft_get_value(e, reg1, e->funcs[car->command].label);
	reg1 += e->funcs[car->command].label;
	val.reg3 = (short)ft_get_value(e, reg1, e->funcs[car->command].label);
	val.reg1 = val.reg3;
	val.reg3 = (car->cur_pos + (val.reg3 + val.reg2) % IDX_MOD);
	ft_flag_sti_show(e, car, reg, &val);
	i = -1;
	while (++i < 4)
	{
		e->fild[ft_check_pos(val.reg3 + i)] =
		(car->reg[reg] >> (8 * (3 - i)) & 255);
	}
	ft_adv_show(e, car, reg1 + 2 - car->cur_pos);
	car->cur_pos = ft_check_pos(reg1 + 2);
}

void		ft_sti_hndl(t_env *e, t_carr *car)
{
	if (car->args[1] == IND_CODE)
		ft_ind_sec(e, car);
	else
		ft_sti(e, car);
}
