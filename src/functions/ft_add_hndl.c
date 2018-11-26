#include "vm.h"

static void ft_flag_add_show(t_env *e, t_carr *car, t_registers *reg)
{
	if ((e->flag_num & 4) == 4)
	{
		printf("P%5d | add ", car->car_index);
		printf("r%d r%d r%d\n", reg->reg1, reg->reg2, reg->reg3);
	}
}

void	ft_add_hndl(t_env *e, t_carr *car)
{
	unsigned int value;
	int pos;
	t_registers reg;
	t_get	f[4];

	ft_set_f(f);
	pos = car->cur_pos + 2;
	reg.reg1 = e->fild[pos];
	reg.reg2 = e->fild[pos + 1];
	value = f[car->args[0]](e, car, &pos) + f[car->args[1]](e, car, &pos);
	car->carry = ((value == 0) ? (1) : (0));
	car->reg[e->fild[pos]] = value;
	reg.reg3 = e->fild[pos];
	ft_flag_add_show(e, car, &reg);
	ft_adv_show(e, car, pos + 1 - car->cur_pos);
	car->cur_pos = pos + 1;
}