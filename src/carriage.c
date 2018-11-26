/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 15:47:53 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/10 15:47:54 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_carlist	*ft_create_car(t_env *e, unsigned int pos, short i, unsigned int nbr)
{
	t_carlist *lst;

	if (!(lst = (t_carlist*)malloc(sizeof(t_carlist))))
		return (NULL);
	lst->carr.cur_pos = pos;
	lst->carr.player = i;
	lst->carr.carry = 0;
	lst->carr.car_index = e->carriage_index;
	lst->carr.reg[0] = nbr;
	lst->carr.killed = 0;
	lst->carr.alive = 0;
	lst->carr.command = 0;
	lst->carr.cycles = 0;
	lst->next = NULL;
	e->carriage_index++;
	return (lst);
}

void	ft_init_carriage(t_env *e)
{
	short i;
	t_carlist *begin;

	//printf("Work here\n");
	i = 1;
	e->head = ft_create_car(e, e->plrs[0].plr_pos, 0, e->plrs[0].n_numb);
	begin = e->head;
	//printf("player id = %d| flag -n value = %u\n", 0, e->head->carr.reg[0]);
	while (i < e->plr_numb)
	{
		e->head->next = ft_create_car(e, e->plrs[i].plr_pos, i, e->plrs[i].n_numb);
		//printf("player id = %d| flag -n value = %u\n", i, e->head->next->carr.reg[0]);
		e->head = e->head->next;
		i++;
	}
	e->head = begin;
}
