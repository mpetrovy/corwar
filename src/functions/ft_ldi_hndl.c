#include "vm.h"

static void	ft_ind_handle(t_env *e, t_carr *car, t_get *f)
{
	int pos;
	unsigned int value;
	unsigned int val1;

	// printf("work ind firsc\n");
	ft_set_f(f);
	pos = car->cur_pos + 2;
	val1 = ft_get_value(e, pos, 2);
	pos += 2;
	// printf("val1 = %x\n", val1);
	val1 = ft_get_value(e, (val1 % IDX_MOD) + car->cur_pos, 4);
	// printf("val1 next = %x\n", val1);
	value = car->cur_pos + ((val1 + f[car->args[1]](e, car, &pos)) % IDX_MOD);
	// printf("value %x\n", value);
	value = ft_get_value(e, value, 4);
	// printf("this value %x reg = %x\n", value, e->fild[pos]);
	car->reg[e->fild[pos]] = value;
	// printf("reg = %x\n", car->reg[e->fild[pos]]);
	car->cur_pos = pos + 1;
		// printf("carrpos %x\n", e->fild[car->cur_pos]);
	// exit (0);
}

static void	ft_handle(t_env *e, t_carr *car, t_get *f)
{
	int pos;
	unsigned int value;

	// printf("work here\n");
	ft_set_f(f);
	pos = car->cur_pos + 2;
	value = car->cur_pos + ((f[car->args[0]](e, car, &pos) + f[car->args[1]](e, car, &pos)) % IDX_MOD);
	// printf("value = %x\n", value);
	value = ft_get_value(e, value, 4);
	car->reg[e->fild[pos]] = value;
	// printf("this value %x reg = %x\n", value, e->fild[pos]);
	// printf("reg = %u\n", car->reg[e->fild[pos]]);
	car->cur_pos = pos + 1;
	// printf("carrpos %x\n", e->fild[car->cur_pos]);
	// exit (0);
}

void	ft_ldi_hndl(t_env *e, t_carr *car)
{
	t_get	f[4];

	car->reg[1] = 5;
	car->reg[2] = 6;
	car->reg[3] = 9;
	printf("LDI HANDLER\n");
	if (car->args[0] == IND_CODE)
		ft_ind_handle(e, car, f);
	else
		ft_handle(e, car, f);
}
