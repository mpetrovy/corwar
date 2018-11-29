/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:44:03 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 21:21:03 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	ft_check_compere(t_env *e, unsigned int id)
{
	int i;

	i = 0;
	while (i < e->plr_numb)
	{
		if (e->plrs[i].n_numb == id)
			return (i);
		i++;
	}
	return (-1);
}

static void	ft_flag_live_show(t_env *e, t_carr *car, short num_plr)
{
	if ((e->flag_num & 4) == 4)
		ft_printf("P%5d | live %d\n", car->car_index, num_plr);
}

static void	ft_flag_player_alive(t_env *e, int player)
{
	if ((e->flag_num & 1) == 1)
	{
		ft_printf("Player %d (%s) is said to be alive\n",
		player + 1, e->plrs[player].head.prog_name);
	}
}

void		ft_live_hndl(t_env *e, t_carr *car)
{
	unsigned int	player;
	int				num_player;

	car->alive = 1;
	e->lives++;
	player = ft_get_value(e, car->cur_pos + 1, 4);
	ft_flag_live_show(e, car, player);
	num_player = ft_check_compere(e, player);
	if (num_player > -1 && num_player <= 4)
	{
		e->winner = num_player + 1;
		ft_flag_player_alive(e, num_player);
	}
	ft_adv_show(e, car, 5);
	car->cur_pos = ft_check_pos(car->cur_pos + 5);
}
