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

void	ft_live_hndl(t_env *e, t_carr *car)
{
	printf("Handle Live command\n");
	unsigned int	player;
	int				num_player;

	player = ft_get_value(e, car->cur_pos + 1, 4);
	num_player = ft_check_compere(e, player);
	if (num_player > -1)
	{
		car->alive = 1;
		e->lives += 1;
		e->plrs[num_player].lifes += 1;
		car->cur_pos += 5;
	}
	else
		car->cur_pos += 5;
}
