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

int	ft_check_valid(t_env *e, t_carr *car, int arg)
{
	int i;
	unsigned char nbr;

	printf("command this %d\n", car->command);
	if (e->funcs[car->command].acb == 0)
	{
		printf("we are here\n");
		return (1);
	}
	nbr = e->fild[car->cur_pos + 1];
	
	printf("nbr = %x\n", nbr);
	i = 0;
	while (i < arg)
	{
		if (((nbr >> (6 - i * 2) & 3) == REG_CODE) && (e->funcs[car->command].arg_t[i] & T_REG) == T_REG)
		{
			printf("REG\n");
			car->args[i] = REG_CODE;
		}
		else if (((nbr >> (6 - i * 2) & 3) == DIR_CODE) && (e->funcs[car->command].arg_t[i] & T_DIR) == T_DIR)
		{
			printf("DIR\n");
			car->args[i] = DIR_CODE;
		}
		else if (((nbr >> (6 - i * 2) & 3) == IND_CODE) && (e->funcs[car->command].arg_t[i] & T_IND) == T_IND)
		{
			printf("IND\n");
			car->args[i] = IND_CODE;
		}
		else
			return (0);
		i++;
	}
	return (1);
}

void	ft_set_handlers(t_hndl *func)
{
	func[1] = &ft_live_hndl;
	func[2] = &ft_ld_hndl;
	func[3] = &ft_st_hndl;
	func[4] = &ft_add_hndl;
	func[5] = &ft_sub_hndl;
	func[6] = &ft_and_hndl;
	func[7] = &ft_or_hndl;
	func[8] = &ft_xor_hndl;
	func[9] = &ft_zjump_hndl;
	func[10] = &ft_ldi_hndl;
	func[11] = &ft_sti_hndl;
	func[12] = &ft_fork_hndl;
	func[13] = &ft_lld_hndl;
	func[14] = &ft_lldi_hndl;
	func[15] = &ft_lfork_hndl;
	func[16] = &ft_aff_hndl;
}

static t_hndl g_func[17];
void	ft_handle_command(t_env *e, t_carr *car)
{
	if (e->fild[car->cur_pos] >= 1 && e->fild[car->cur_pos] <= 16)
	{
		if (car->command == 0)
		{
			car->command = e->fild[car->cur_pos];
			car->cycles = e->funcs[car->command].cycles;
			car->working = 1;
		}
		if (car->working == 0 && car->cycles == 0)
		{
			if (ft_check_valid(e, car, e->funcs[car->command].args))
			{
				g_func[car->command](e, car);
				car->command = 0;
			}
			else
				ft_error("./corewar", "not valid <> arguments");
		}
		else
		{
			car->cycles--;
			if (car->cycles == 0)
				car->working = 0;
		}
	}
	//else
		//car->cur_pos++;
}

void	ft_update(t_env *e)
{
	t_carlist *begin;

	begin = e->head;
	while (begin)
	{
		if (begin->carr.cur_pos == MEM_SIZE)
			begin->carr.cur_pos = 0;
		printf("nbr car %d\n", begin->carr.car_index);
		printf("nbr 1 = %d nbr 2 = %d\n", begin->carr.cur_pos, begin->carr.cur_pos + 1);
		printf("command = %x next %x pos = %u player = %d\n", e->fild[begin->carr.cur_pos], e->fild[begin->carr.cur_pos + 1], begin->carr.cur_pos, begin->carr.player);
		ft_handle_command(e, &begin->carr);
		
		//begin->carr.cur_pos++;
		begin = begin->next;
	}
	// e->head = begin;
}

void	ft_carriage_run(t_env *e)
{
	short	live;
	int		cycles;

	cycles = 0;
	live = 1;
	ft_set_handlers(g_func);
	while (live)
	{
		if (cycles == 40000) 
			break ;
		// if (e->head->carr.cur_pos == 4096)
		// 	break ;
		printf("\ncycle = %d\n\n", cycles);
		printf("lifes player 0 = %d\n", e->plrs[0].lifes);
		ft_update(e);
		cycles++;
	}
}
