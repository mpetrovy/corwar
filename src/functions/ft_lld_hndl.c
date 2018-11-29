/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld_hndl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:21:10 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 21:21:12 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	ft_dir_first(t_env *e, t_carr *car)
{
	unsigned int	value;
	int				pos;
	int				reg;

	pos = ft_check_pos(car->cur_pos + 2);
	value = ft_get_value(e, pos, e->funcs[car->command].label);
	pos += e->funcs[car->command].label;
	reg = e->fild[pos];
	if (reg > 0 && reg <= REG_NUMBER)
	{
		car->reg[reg] = value;
		if (value == 0)
			car->carry = 1;
		else
			car->carry = 0;
	}
	car->cur_pos = ft_check_pos(pos + 1);
}

static void	ft_ind_first(t_env *e, t_carr *car)
{
	unsigned int	ind;
	int				pos;
	int				value;

	pos = ft_check_pos(car->cur_pos + 2);
	ind = ft_get_value(e, pos, 2);
	pos += 2;
	value = ft_get_value(e, car->cur_pos + ind, 4);
	car->carry = ((value == 0) ? (1) : (0));
	car->reg[e->fild[pos]] = value;
	car->cur_pos = ft_check_pos(pos + 1);
}

void		ft_lld_hndl(t_env *e, t_carr *car)
{
	if (car->args[0] == DIR_CODE)
		ft_dir_first(e, car);
	else
		ft_ind_first(e, car);
}
