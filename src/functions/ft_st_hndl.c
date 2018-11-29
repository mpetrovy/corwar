/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st_hndl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:21:43 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 21:21:43 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_flag_st_show(t_env *e, t_carr *car, unsigned int reg, int val)
{
	if ((e->flag_num & 4) == 4)
	{
		ft_printf("P%5d | st r%d %d\n", car->car_index, reg, val);
	}
}

static void	ft_ind_first(t_env *e, t_carr *car)
{
	int		reg;
	int		pos;
	int		value;

	pos = ft_check_pos(car->cur_pos + 2);
	reg = e->fild[ft_check_pos(pos++)];
	value = (short)ft_get_value(e, pos, 2);
	value = (value % IDX_MOD);
	if (reg > 0 && reg <= REG_NUMBER)
	{
		car->i = -1;
		while (++car->i < 4)
		{
			e->fild[ft_check_pos(car->cur_pos + value + car->i)] =
			((car->reg[reg] >> (8 * (3 - car->i))) & 255);
		}
		ft_flag_st_show(e, car, reg, value);
		ft_adv_show(e, car, pos + 2 - car->cur_pos);
		car->cur_pos = ft_check_pos(pos + 2);
	}
	else
	{
		ft_check_codage(e, car, &car->i, &car->cod);
		car->cur_pos = ft_check_pos(car->cur_pos + 2 + car->ofset);
	}
}

static void	ft_reg_first(t_env *e, t_carr *car)
{
	int	reg1;
	int	reg2;
	int	pos;

	pos = ft_check_pos(car->cur_pos + 2);
	reg1 = e->fild[ft_check_pos(pos++)];
	reg2 = e->fild[ft_check_pos(pos)];
	if (reg2 > 0 && reg2 <= REG_NUMBER && reg1 > 0 && reg1 <= REG_NUMBER)
		car->reg[reg2] = car->reg[reg1];
	car->cur_pos = ft_check_pos(pos + 1);
}

void		ft_st_hndl(t_env *e, t_carr *car)
{
	if (car->args[1] == IND_CODE)
		ft_ind_first(e, car);
	else if (car->args[1] == REG_CODE)
		ft_reg_first(e, car);
}
