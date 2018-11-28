#include "vm.h"

static t_hndl g_func[17];

static int	ft_check_valid(t_env *e, t_carr *car, int arg)
{
	int i;
	unsigned char nbr;

	if (e->funcs[car->command].zero_code == 0)
		return (1);// обработать смещение карретки в соотвествие с ее кол-вом аргументов
	nbr = e->fild[car->cur_pos + 1];
	i = 0;
	while (i < arg)
	{
		if (((nbr >> (6 - i * 2) & 3) == REG_CODE) && (e->funcs[car->command].arg_t[i] & T_REG) == T_REG)
			car->args[i] = REG_CODE;
		else if (((nbr >> (6 - i * 2) & 3) == DIR_CODE) && (e->funcs[car->command].arg_t[i] & T_DIR) == T_DIR)
			car->args[i] = DIR_CODE;
		else if (((nbr >> (6 - i * 2) & 3) == IND_CODE) && (e->funcs[car->command].arg_t[i] & T_IND) == T_IND)
			car->args[i] = IND_CODE;
		else
			return (0);// обработать смещение карретки в соотвествие с ее кол-вом аргументов
		i++;
	}
	return (1);
}

static void    ft_move_carr(t_env *e, t_carr *car)
{
    if (car->command == 0)
	{
		car->command = e->fild[car->cur_pos];
		car->cycles = e->funcs[car->command].cycles - 1;
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
			car->cur_pos++;
	}
	else
	{
		car->cycles--;
		if (car->cycles == 0)
			car->working = 0;
	}
}


static void	ft_handle_command(t_env *e, t_carr *car)
{
	if (e->fild[car->cur_pos] >= 1 && e->fild[car->cur_pos] <= 16)
	{
		ft_move_carr(e, car);
	}
	else
		car->cur_pos++;
}

void	ft_update(t_env *e)
{
	t_carlist *begin;

	begin = e->head;
	while (begin)
	{
		if (begin->carr.cur_pos == MEM_SIZE)
			begin->carr.cur_pos = 0;
		ft_handle_command(e, &begin->carr);
		begin = begin->next;
	}
}

void ft_carstep(t_env *e, int *cycles)
{
	short	live;
	int		cur_cycle;

	cur_cycle = 1;
	live = 1;
	ft_set_handlers(g_func);
	while (live)
	{
		if (*cycles == e->dump)
			break ;
		if ((e->flag_num & 2) == 2)
			printf("It is now cycle %d\n", *cycles);
		ft_update(e);
		if (cur_cycle == e->cycle_to_die)
		{
			ft_check_cycle(e, &live);
			cur_cycle = 0;
		}
		(*cycles)++;
		cur_cycle++;
	}
}