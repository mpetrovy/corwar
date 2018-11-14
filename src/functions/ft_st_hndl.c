#include "vm.h"

static void ft_ind_first(t_env *e, t_carr *car)
{
	int				reg;
	int				pos;
	unsigned int	value;
	int				i;
	int				pos_from;

	car->reg[1] = 0xffffffed;//check initialization of registers
	pos_from = car->cur_pos;
	pos = car->cur_pos + 2;
	//printf("fild %x\n", e->fild[pos]);
	reg = e->fild[pos++];
	//printf("fild %x \n", e->fild[pos]);
	value = (ft_get_value(e, pos, 2) % IDX_MOD);
	//printf("value %d\n", value);
	//printf("value change %x\n", e->fild[pos + value]);
	i = -1;
	while (++i < 4)
	{
	//	printf("before %x ", e->fild[pos + value + i]);
		e->fild[pos_from + value + i] = ((car->reg[reg] >> (8 * (3 - i))) & 255);
	//	printf("after %x\n", e->fild[pos + value + i]);
	}
//	printf("after %x\n", e->fild[pos + value + i]);
	//e->fild[pos + value] = car->reg[reg];
//	printf("value %d\n", value);
	car->cur_pos = pos + 2;
//	printf("data %x\n", e->fild[car->cur_pos]);
	//exit (0);
}

static void	ft_reg_first(t_env *e, t_carr *car)
{
	int reg1;
	int reg2;
	int pos;
	printf("REG is first argument");

	pos = car->cur_pos + 2;
	reg1 = e->fild[pos++];
	reg2 = e->fild[pos];
	if (reg2 > 0 && reg2 <= REG_NUMBER && reg1 > 0 && reg1 <= REG_NUMBER)
		car->reg[reg2] = car->reg[reg1];
	car->cur_pos = pos + 1;
}

void	ft_st_hndl(t_env *e, t_carr *car)
{
		printf("Inside st\n");
	if (car->args[1] == IND_CODE)
	{
		ft_ind_first(e, car);
	}
	else if (car->args[1] == REG_CODE)
	{
		ft_reg_first(e, car);
	}
}