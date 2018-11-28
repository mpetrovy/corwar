/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xor_hndl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 04:04:31 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 04:04:33 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_flag_xor_show(t_env *e, t_carr *car, t_intstruct *val, int var)
{
	if ((e->flag_num & 4) == 4)
		printf("P%5d | xor %d %d r%d\n", car->car_index, var, val->reg1, val->reg3);
}

void			ft_xor_hndl(t_env *e, t_carr *car)
{
	int			pos;
	t_intstruct	val;
	int			var;
	t_get		f[4];

	ft_set_f(f);
	pos = car->cur_pos + 2;
	val.reg1 = f[car->args[0]](e, car, &pos);
	var = f[car->args[1]](e, car, &pos);
	val.reg2 = val.reg1 ^ var;
	val.reg3 = e->fild[pos];
	ft_flag_xor_show(e, car, &val, var);
	car->carry = ((val.reg2 == 0) ? (1) : (0));
	car->reg[val.reg3] = val.reg2;
	ft_adv_show(e, car, pos + 1 - car->cur_pos);
	car->cur_pos = pos + 1;
}
