/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff_hndl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:19:52 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 21:19:53 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_aff_hndl(t_env *e, t_carr *car)
{
	int	reg;
	int	pos;

	pos = ft_check_pos(car->cur_pos + 2);
	reg = e->fild[pos];
	if (reg > 0 && reg <= REG_NUMBER)
		ft_printf("%c\n", (car->reg[reg] % 256));
	car->cur_pos = ft_check_pos(pos + 1);
}
