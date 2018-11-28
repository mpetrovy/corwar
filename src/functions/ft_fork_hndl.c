#include "vm.h"

static void	ft_copy(unsigned int *dst, unsigned int *cp)
{
	int i;

	i = 0;
	while (i < REG_NUMBER)
	{
		dst[i] = cp[i];
		i++;
	}
}

static void	ft_flag_fork_show(t_env *e, t_carr *car, int value)
{
	if ((e->flag_num & 4) == 4)
	{
		printf("P%5d | fork %d (%d)\n", car->car_index, value,
		car->cur_pos + (value % IDX_MOD));
	}
}

static void	ft_add_cursor(t_env *e, t_carr *car, int pos)
{
	t_carlist *lst;
	t_carlist *tmp;

	tmp = e->head;
	if (!(lst = (t_carlist*)malloc(sizeof(t_carlist))))
		return ;
	lst->carr.cur_pos = ft_check_pos(car->cur_pos + (pos % IDX_MOD));
	lst->carr.player = car->player;
	lst->carr.car_index = e->carriage_index;
	lst->carr.carry = car->carry;
	ft_copy(lst->carr.reg, car->reg);
	//lst->carr.reg[0] = car->reg[0];
	//printf("live %d\n", car->alive);
	// lst->carr.killed = car->killed;
	lst->carr.alive = car->alive;
	lst->carr.command = 0;
	lst->carr.cycles = 0;
	lst->next = tmp;
	e->head = lst;
	e->carriage_index++;
}

void	ft_fork_hndl(t_env *e, t_carr *car)
{
	short	value;
	int		step;

	step = 3;
	// printf("flag %d\n", e->flag_num);
	// printf("fork working\n"); //delete
	value = (short)ft_get_value(e, car->cur_pos + 1, 2);
	//printf("P %d | fork %u ()\n", car->car_index, value);
	ft_add_cursor(e, car, value);
	ft_flag_fork_show(e, car, value);
	ft_adv_show(e, car, step);
	car->cur_pos += step;
	// printf("%x %x %x %x\n", e->fild[car->cur_pos], e->fild[car->cur_pos + 1], e->fild[car->cur_pos + 2], e->fild[car->cur_pos + 3]);
	//exit (0);
}