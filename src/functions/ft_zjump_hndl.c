#include "vm.h"

static void ft_flag_zjump_show(t_env *e, t_carr *car, int step)
{
	if ((e->flag_num & 4) == 4)
	{
		printf("P%5d | zjmp %d ", car->car_index, step);
		(car->carry == 1) ? (printf("OK\n")) : (printf("FAILED\n"));
	}
}

// static int ft_check_pos(int pos)
// {
// 	return (((unsigned)(MEM_SIZE + pos)) % MEM_SIZE);
// }

void	ft_zjump_hndl(t_env *e, t_carr *car)
{
	short position;
	//printf("WE are handled ZJUMP\n");
	if (car->carry == 1)
	{
		//printf("position %x car_pos = %u\n", e->fild[car->cur_pos], car->cur_pos);
		position = ft_get_value(e, car->cur_pos + 1, e->funcs[car->command].label); // занчение на которое смещать каретку
		//printf("value %x\n", value);
	
		position %= IDX_MOD; // T_DIR % IDX_MOD
		//printf("value1 = %d\n", position);
		car->cur_pos = ft_check_pos(position + car->cur_pos); // смещение каретки на значение
		
		//printf("last_pos %d new pos %d\n", last_pos, car->cur_pos);
		ft_flag_zjump_show(e, car, position);
	}
	else
		car->cur_pos += 3;
	// exit (0);
}