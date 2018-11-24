#include "vm.h"

void	ft_zjump_hndl(t_env *e, t_carr *car)
{
	unsigned int value;
	printf("WE are handled ZJUMP\n");
	if (car->carry == 1)
	{
		printf("position %x car_pos = %u\n", e->fild[car->cur_pos], car->cur_pos);
		value = ft_get_value(e, car->cur_pos + 1, e->funcs[car->command].label);
		printf("value %x\n", value);
		value %= IDX_MOD;
		printf("value1 = %x\n", value);
		car->cur_pos += value;
		car->cur_pos = MODA(car->cur_pos);
		printf("position %x car_pos = %u\n", e->fild[car->cur_pos], car->cur_pos);
	}
	else
		car->cur_pos += 3;
	// exit (0);
}