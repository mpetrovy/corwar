#include "vm.h"

static void ft_ind_sec(t_env *e, t_carr *car)
{
	unsigned int pos;
	unsigned int val1;
	unsigned int val2;
	int reg;
	int i;

	printf("TESTING NEEDED ALARM ALARM\n");
	//printf("data %x\n", e->fild[car->cur_pos]);
	car->reg[1] = 0xffffffff;
	reg = e->fild[car->cur_pos + 2];
	pos = car->cur_pos + 3;
	val1 = ft_get_value(e, pos, e->funcs[car->command].label);
	//printf("val1 %x\n", val1);
	val1 = ft_get_value(e, (val1 % IDX_MOD), 4);
	pos += e->funcs[car->command].label;
	//printf("data %x\n", e->fild[pos]);
	val2 = ft_get_value(e, pos, e->funcs[car->command].label);
	//printf("val2 %x\n", val2);
	val1 += val2;
	val2 = (val1 + car->cur_pos) % IDX_MOD;
//	printf("sum %x\n", val1);
	i = -1;
	while (++i < 4)
	{
		e->fild[val2 + i] = (car->reg[reg] >> (8 * (3 - i)) & 255);
	}
	car->cur_pos = pos + 2;
	printf("data %x\n", e->fild[car->cur_pos]);
	//exit(0);
}

static void	ft_sti(t_env *e, t_carr *car)
{
	unsigned int pos;
	unsigned int val1;
	unsigned int val2;
	int reg;
	int i;

	//printf("data %x\n", e->fild[car->cur_pos]);
	car->reg[1] = 0xffffffff; // find out how to make initialization
	reg = e->fild[car->cur_pos + 2];
	pos = car->cur_pos + 3;
	val1 = ft_get_value(e, pos, e->funcs[car->command].label);
	//printf("val1 %x\n", val1);
	pos += e->funcs[car->command].label;
	//printf("data %x\n", e->fild[pos]);
	val2 = ft_get_value(e, pos, e->funcs[car->command].label);
	//printf("val2 %x\n", val2);
	val1 += val2;
	val2 = (val1 + car->cur_pos) % IDX_MOD;
//	printf("sum %x\n", val1);
	i = -1;
	while (++i < 4)
	{
		e->fild[val2 + i] = (car->reg[reg] >> (8 * (3 - i)) & 255);
	}
	car->cur_pos = pos + 2;
	printf("data %x\n", e->fild[car->cur_pos]);
	//exit(0);
}

void	ft_sti_hndl(t_env *e, t_carr *car)
{
	printf("STI HANDLED\n");
	if (car->args[1] == IND_CODE)
		ft_ind_sec(e, car);
	else
		ft_sti(e, car);	
}