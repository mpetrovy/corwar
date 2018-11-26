#include "vm.h"

static void	ft_flag_sti_show(t_env *e, t_carr *car, int reg, unsigned int val1, unsigned int val2)
{
	if ((e->flag_num & 4) == 4)
	{
		printf("P%5d | sti r%d %u %u\n", car->car_index, reg, val1, val2);
		printf("       | -> store to %u + %u = %u (with pc and mod %u)\n",
			val1, val2, val1 + val2, val1 + val2);
	}
}

static void ft_ind_sec(t_env *e, t_carr *car)
{
	unsigned int pos;
	unsigned int val1;
	unsigned int val2;
	int reg;
	int i;

	//printf("TESTING NEEDED ALARM ALARM\n");
	car->reg[1] = 0xffffffff; // find out how to make initialization
	reg = e->fild[car->cur_pos + 2];
	pos = car->cur_pos + 3;
	val1 = ft_get_value(e, pos, e->funcs[car->command].label);
	val1 = ft_get_value(e, (val1 % IDX_MOD), 4);
	pos += e->funcs[car->command].label;
	val2 = ft_get_value(e, pos, e->funcs[car->command].label);
	val1 += val2;
	ft_flag_sti_show(e, car, reg, val1, val2);
	val2 = (val1 + car->cur_pos) % IDX_MOD;
	i = -1;
	while (++i < 4)
		e->fild[val2 + i] = (car->reg[reg] >> (8 * (3 - i)) & 255);
	ft_adv_show(e, car, pos + 2 - car->cur_pos);
	car->cur_pos = pos + 2;
}

static void	ft_sti(t_env *e, t_carr *car)
{
	unsigned int pos;
	unsigned int val1;
	unsigned int val2;
	int reg;
	int i;

	car->reg[1] = 0xffffffff; // find out how to make initialization
	reg = e->fild[car->cur_pos + 2];
	pos = car->cur_pos + 3;
	val1 = ft_get_value(e, pos, e->funcs[car->command].label);
	pos += e->funcs[car->command].label;
	val2 = ft_get_value(e, pos, e->funcs[car->command].label);
	ft_flag_sti_show(e, car, reg, val1, val2);
	val1 += val2;
	val2 = (val1 + car->cur_pos) % IDX_MOD;
	i = -1;
	while (++i < 4)
		e->fild[val2 + i] = (car->reg[reg] >> (8 * (3 - i)) & 255);
	ft_adv_show(e, car, pos + 2 - car->cur_pos);
	car->cur_pos = pos + 2;
}

void	ft_sti_hndl(t_env *e, t_carr *car)
{
	if (car->args[1] == IND_CODE)
		ft_ind_sec(e, car);
	else
		ft_sti(e, car);	
}