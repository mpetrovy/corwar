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

static void			ft_clean_reg(unsigned int *arr)
{
	int	i;

	i = 0;
	while (i < REG_NUMBER + 1)
	{
		arr[i] = 0;
		i++;
	}
}

static t_carlist	*ft_create_car(t_env *e, unsigned int pos, short i,
unsigned int nbr)
{
	t_carlist	*lst;

	if (!(lst = (t_carlist*)malloc(sizeof(t_carlist))))
		return (NULL);
	ft_clean_reg(lst->carr.reg);
	lst->carr.cur_pos = pos;
	lst->carr.player = i;
	lst->carr.carry = 0;
	lst->carr.car_index = e->carriage_index;
	lst->carr.reg[1] = nbr;
	lst->carr.alive = 0;
	lst->carr.command = 0;
	lst->carr.cycles = 0;
	lst->next = NULL;
	e->carriage_index++;
	return (lst);
}

void				ft_init_carriage(t_env *e)
{
	short		i;
	t_carlist	*begin;
	t_carlist	*tmp;

	i = 1;
	e->head = ft_create_car(e, e->plrs[0].plr_pos, 0, e->plrs[0].n_numb);
	begin = e->head;
	while (i < e->plr_numb)
	{
		tmp = ft_create_car(e, e->plrs[i].plr_pos, i, e->plrs[i].n_numb);
		tmp->next = e->head;
		e->head = tmp;
		i++;
	}
}
