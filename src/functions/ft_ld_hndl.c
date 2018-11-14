/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:12:23 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/07 18:12:25 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned int	ft_get_value(t_env *e, int cur_pos, int label)
{
	if (label == 2)
		return ((e->fild[cur_pos] << 8) | (e->fild[cur_pos + 1]));
	else if (label == 4)
		return ((e->fild[cur_pos] << 24) | (e->fild[cur_pos + 1] << 16) | (e->fild[cur_pos + 2] << 8) | (e->fild[cur_pos + 3]));
	return (0);
}

void	ft_dir_first(t_env *e, t_carr *car)
{
	unsigned int value;
	int				pos;
	int				reg;

	pos = car->cur_pos + 2;
	value = ft_get_value(e, pos, e->funcs[car->command].label);
	pos += e->funcs[car->command].label;
	reg = e->fild[pos];
	if (reg > 0 && reg <= REG_NUMBER)
	{
		car->reg[reg] = value;
		(value == 0) ? (car->carry = 1) : (car->carry = 0);
	}
	car->cur_pos = pos + 1;
}

void	ft_ind_first(t_env *e, t_carr *car)
{
	(void)e;
	(void)car;
}

void	ft_ld_hndl(t_env *e, t_carr *car)
{
	printf("we are inside of load func\n");
	if (car->args[0] == DIR_CODE)
		ft_dir_first(e, car);
	else
		ft_ind_first(e, car);
}
