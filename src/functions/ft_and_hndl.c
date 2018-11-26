#include "vm.h"

static void	ft_flag_and_show(t_env *e, t_carr *car, int reg, unsigned int val1, unsigned int val2)
{
	if ((e->flag_num & 4) == 4)
		printf("P%5d | and %d %u r%d\n", car->car_index, val1, val2, reg);//change on ft_printf
}

void	ft_and_hndl(t_env *e, t_carr *car)
{
	int pos;
	int reg;
	unsigned int value;
	t_get	f[4];
	unsigned int var;

	ft_set_f(f);
	pos = car->cur_pos + 2;
	var = f[car->args[0]](e, car, &pos);
	value = var & f[car->args[1]](e, car, &pos);
	reg = e->fild[pos];
	ft_flag_and_show(e, car, reg, var, value);
	car->carry = ((value == 0) ? (1) : (0));
	car->reg[reg] = value;
	ft_adv_show(e, car, pos + 1 - car->cur_pos);
	car->cur_pos = pos + 1;
}