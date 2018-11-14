#include "vm.h"

void	ft_xor_hndl(t_env *e, t_carr *car)
{
	int pos;
	int reg;
	unsigned int value;
	t_get	f[4];

//	printf("inside in\n");
	// car->reg[1] = 5;
	// car->reg[2] = 5;
	ft_set_f(f);
	pos = car->cur_pos + 2;
	value = f[car->args[0]](e, car, &pos) ^ f[car->args[1]](e, car, &pos);
	reg = e->fild[pos];
	printf("reg = %d\n", reg);
	//printf("value = %u\n", value);
	car->carry = ((value == 0) ? (1) : (0));
	car->reg[reg] = value;
	car->cur_pos = pos + 1;
	printf("reg = %u\n", car->reg[reg]);
	printf("position %x\n", e->fild[car->cur_pos]);
}