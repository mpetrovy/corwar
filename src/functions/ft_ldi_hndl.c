/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi_hndl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:20:43 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 21:20:45 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_ind_handle(t_env *e, t_carr *car, t_get *f)
{
	int				pos;
	unsigned int	value;
	unsigned int	val1;
	int				reg;

	ft_set_f(f);
	pos = ft_check_pos(car->cur_pos + 2);
	val1 = ft_get_value(e, pos, 2);
	pos = ft_check_pos(pos + 2);
	val1 = ft_get_value(e, (val1 % IDX_MOD) + car->cur_pos, 4);
	value = car->cur_pos + ((val1 + f[car->args[1]](e, car, &pos)) % IDX_MOD);
	value = ft_get_value(e, value, 4);
	reg = e->fild[ft_check_pos(pos)];
	if (reg > 0 && reg <= REG_NUMBER)
	{
		car->reg[reg] = value;
		car->cur_pos = ft_check_pos(pos + 1);
	}
	else
	{
		ft_check_codage(e, car, &car->i, &car->cod);
		car->cur_pos = ft_check_pos(car->cur_pos + 2 + car->ofset);
	}
}

static void	ft_handle(t_env *e, t_carr *car, t_get *f)
{
	int				pos;
	unsigned int	value;
	unsigned int	val1;
	unsigned int	val2;
	int				reg;

	ft_set_f(f);
	pos = ft_check_pos(car->cur_pos + 2);
	val1 = f[car->args[0]](e, car, &pos);
	pos = ft_check_pos(pos);
	val2 = f[car->args[1]](e, car, &pos);
	value = car->cur_pos + ((val1 + val2) % IDX_MOD);
	value = ft_get_value(e, value, 4);
	reg = e->fild[ft_check_pos(pos)];
	if (reg > 0 && reg <= REG_NUMBER)
	{
		car->reg[reg] = value;
		car->cur_pos = ft_check_pos(pos + 1);
	}
	else
	{
		ft_check_codage(e, car, &car->i, &car->cod);
		car->cur_pos = ft_check_pos(car->cur_pos + 2 + car->ofset);
	}
}

void		ft_ldi_hndl(t_env *e, t_carr *car)
{
	t_get	f[4];

	if (car->args[0] == IND_CODE)
		ft_ind_handle(e, car, f);
	else
		ft_handle(e, car, f);
}
