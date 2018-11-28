#include "vm.h"

void	ft_aff_hndl(t_env *e, t_carr *car)
{
	int reg;
	int pos;

	printf("TEST AFF COMMAND\n");
	pos = car->cur_pos + 2;
	reg = e->fild[pos];
	ft_putchar((car->reg[reg] % 256));
	car->cur_pos = pos + 1;
	//exit (0);
}