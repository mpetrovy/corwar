/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lldi_hndl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:21:16 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 21:21:17 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_ind_handle(t_env *e, t_carr *car, t_get *f)
{
	int				pos;
	unsigned int	value;
	unsigned int	val1;

	ft_set_f(f);
	pos = ft_check_pos(car->cur_pos + 2);
	val1 = ft_get_value(e, pos, 2);
	pos += 2;
	val1 = ft_get_value(e, (val1 % IDX_MOD) + car->cur_pos, 4);
	value = car->cur_pos + (val1 + f[car->args[1]](e, car, &pos));
	value = ft_get_value(e, value, 4);
	car->reg[e->fild[pos]] = value;
	car->cur_pos = ft_check_pos(pos + 1);
}

static void	ft_handle(t_env *e, t_carr *car, t_get *f)
{
	int pos;
	int value;

	ft_set_f(f);
	pos = ft_check_pos(car->cur_pos + 2);
	value = car->cur_pos + ((f[car->args[0]](e, car, &pos) +
	f[car->args[1]](e, car, &pos)) % IDX_MOD);
	value = ft_get_value(e, value, 4);
	car->reg[e->fild[pos]] = value;
	car->cur_pos = ft_check_pos(pos + 1);
}

void		ft_lldi_hndl(t_env *e, t_carr *car)
{
	t_get	f[4];

	if (car->args[0] == IND_CODE)
		ft_ind_handle(e, car, f);
	else
		ft_handle(e, car, f);
}
