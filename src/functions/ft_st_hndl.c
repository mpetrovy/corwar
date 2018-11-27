#include "vm.h"

static void ft_flag_st_show(t_env *e, t_carr *car, unsigned int reg, unsigned int val)
{
	if ((e->flag_num & 4) == 4)
	{
		printf("P%5d | st r%d %d\n", car->car_index, reg, val);
	}
}

static void ft_ind_first(t_env *e, t_carr *car)
{
	int		reg;
	int		pos;
	short	value;
	int		i;
	int		pos_from;

	///car->reg[1] = 0xffffffed;//check initialization of registers
	pos_from = car->cur_pos;
	pos = car->cur_pos + 2;
	reg = e->fild[pos++];
	value = ((short)ft_get_value(e, pos, 2) % IDX_MOD);
	i = -1;
	while (++i < 4)
	{
		//printf("Position %u\n", ft_check_pos(pos_from + value + i));
		e->fild[ft_check_pos(pos_from + value + i)] = ((car->reg[reg] >> (8 * (3 - i))) & 255);
	}
	ft_flag_st_show(e, car, reg, value);
	ft_adv_show(e, car, pos + 2 - car->cur_pos);
	car->cur_pos = pos + 2;
}

static void	ft_reg_first(t_env *e, t_carr *car)
{
	int reg1;
	int reg2;
	int pos;
	//printf("REG is first argument\n");// what is the output must be here

	pos = car->cur_pos + 2;
	reg1 = e->fild[pos++];
	reg2 = e->fild[pos];
	if (reg2 > 0 && reg2 <= REG_NUMBER && reg1 > 0 && reg1 <= REG_NUMBER)
		car->reg[reg2] = car->reg[reg1];
	car->cur_pos = pos + 1;
}

void	ft_st_hndl(t_env *e, t_carr *car)
{
	if (car->args[1] == IND_CODE)
		ft_ind_first(e, car);
	else if (car->args[1] == REG_CODE)
		ft_reg_first(e, car);
}