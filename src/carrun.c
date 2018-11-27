/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carrun.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:36:06 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/07 18:36:07 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void ft_end_prog(t_env *e, int cycles)
{
	if (cycles == e->dump)
	{
		ft_show_for_debug(e);
	}
	else
	{
		//printf("number = %d\n", e->winner);
		printf("Contestant %d, \"%s\", has won !\n",
		e->winner, e->plrs[e->winner - 1].head.prog_name);
	}
}

void	ft_carriage_run(t_env *e)
{
	int		cycles;
	
	cycles = 1;
	if (e->dump != 0)
		ft_carstep(e, &cycles);
	if ((e->flag_num & 2) == 2)
		printf("It is now cycle %d\n", cycles);
	ft_update(e);
    ft_check_killed_carriage(e);
    ft_check_killed_carriage(e);
	ft_end_prog(e, cycles);
}
