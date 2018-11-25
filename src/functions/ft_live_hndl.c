/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:44:03 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/07 17:44:07 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	ft_check_compere(t_env *e, unsigned int id)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (e->plrs[i].n_numb == id)
			return (i);
		i++;
	}
	return (-1);
}

static void	ft_flag_live_show(t_env *e, t_carr *car, unsigned int num_plr, int player)
{
	if ((e->flag_num & 4) == 4)
	{
		printf("P   %d | live %u\n", car->car_index, num_plr);
	}
	if ((e->flag_num & 1) == 1)
	{
		printf("Player %d (%s) is said to be alive\n", player, e->plrs[player].head.prog_name);
	}
}

void	ft_live_hndl(t_env *e, t_carr *car)
{
	unsigned int	player;
	int				num_player;

	player = ft_get_value(e, car->cur_pos + 1, 4);
	ft_flag_live_show(e, car, player, 0);
	num_player = ft_check_compere(e, player);
	ft_adv_show(e, car, 5);
	if (num_player > -1)
	{
		car->alive = 1;
		e->lives += 1;
		e->winner = num_player;
		e->plrs[num_player].lifes += 1;
		ft_flag_live_show(e, car, 0, num_player);
		car->cur_pos += 5;
	}
	else
		car->cur_pos += 5;
}
