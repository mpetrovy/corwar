#include "vm.h"

static void ft_flag_zjump_show(t_env *e, t_carr *car, int step)
{
	if ((e->flag_num & 4) == 4)
	{
		printf("P%5d | zjmp %d ", car->car_index, step);
		(car->carry == 1) ? (printf("OK\n")) : (printf("FAILED\n"));
	}
}

void	ft_zjump_hndl(t_env *e, t_carr *car)
{
	int last_pos;
	int value;
	//printf("WE are handled ZJUMP\n");
	if (car->carry == 1)
	{
		last_pos = car->cur_pos; // позиция на которой стояла изначально каретка
	//	printf("position %x car_pos = %u\n", e->fild[car->cur_pos], car->cur_pos);
		value = ft_get_value(e, car->cur_pos + 1, e->funcs[car->command].label); // занчение на которое смещать каретку
		//printf("value %x\n", value);
		value %= MEM_SIZE;//IDX_MOD; // T_DIR % IDX_MOD
		//printf("value1 = %x\n", value);
		car->cur_pos += value; // смещение каретки на значение
		if (car->cur_pos > 4096)
			car->cur_pos -= 4096;
		//printf("last_pos %d new pos %d\n", last_pos, car->cur_pos);
		ft_flag_zjump_show(e, car, car->cur_pos - last_pos);
		//car->cur_pos = MODA(car->cur_pos);
		//printf("position %x car_pos = %u\n", e->fild[car->cur_pos], car->cur_pos);
	}
	else
		car->cur_pos += 3;
}