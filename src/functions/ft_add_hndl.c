#include "vm.h"

void	ft_add_hndl(t_env *e, t_carr *car)
{
	unsigned int value;
	int pos;
	t_get	f[4];

	ft_set_f(f);
	// car->reg[1] = 2;
	// car->reg[2] = 3; //initiallization of registers 
	// car->reg[3] = 4;
	printf("ADD HANDLE\n");
	pos = car->cur_pos + 2;
	value = f[car->args[0]](e, car, &pos) + f[car->args[1]](e, car, &pos);
	printf("sum of reg1 + reg2 = value %x\n", value);
	car->carry = ((value == 0) ? (1) : (0));
	printf("privious value of final reg = %x\n", car->reg[e->fild[pos]]);
	car->reg[e->fild[pos]] = value;
	printf("value of reg after all = %x\n", car->reg[e->fild[pos]]);
	car->cur_pos = pos + 1;
	printf("position %x\n", e->fild[car->cur_pos]);
	// exit (0);
}