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
	while (i < e->plr_numb)
	{
		if (e->plrs[i].n_numb == id)
		{
			//printf("players = %u == %u\n", e->plrs[i].n_numb, id);
			return (i);
		}
		i++;
	}
	return (-1);
}

static void	ft_flag_live_show(t_env *e, t_carr *car, short num_plr)
{
	if ((e->flag_num & 4) == 4)
		printf("P%5d | live %d\n", car->car_index, num_plr);
}

static void	ft_flag_player_alive(t_env *e, int player)
{
	if ((e->flag_num & 1) == 1)
		printf("Player %d (%s) is said to be alive\n", player + 1, e->plrs[player].head.prog_name);
}

void	ft_live_hndl(t_env *e, t_carr *car)
{
	unsigned int	player;
	int				num_player;

	car->alive = 1;
	e->lives++;
	//printf("fild [%u] = %x [%u] = %x [%u] = %x [%u] = %x\n",car->cur_pos + 1, e->fild[car->cur_pos + 1], car->cur_pos + 2, e->fild[car->cur_pos + 2], car->cur_pos + 3, e->fild[car->cur_pos + 3], car->cur_pos + 4, e->fild[car->cur_pos + 4]);
	player = (short)ft_get_value(e, car->cur_pos + 1, 4);
	ft_flag_live_show(e, car, player);
	num_player = ft_check_compere(e, player);
	//printf("player %u num_plr %d\n", player, num_player);
	if (num_player > -1)
	{
		//printf("inside\n");
	//	printf("num_player %u\n", num_player);
		e->winner = num_player + 1;
		//e->plrs[num_player].lifes += 1;
		ft_flag_player_alive(e, num_player);
		//exit (0);
	}
	ft_adv_show(e, car, 5);
	car->cur_pos += 5;
	//printf("did car live %d car_index %d\n", car->alive, car->car_index);
}
