#include "vm.h"

static void	ft_flag_sti_show(t_env *e, t_carr *car, int reg, t_intstruct *val)
{
	if ((e->flag_num & 4) == 4)
	{
		printf("P%5d | sti r%d %d %d\n", car->car_index, reg, val->reg2, val->reg1);
		printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			val->reg2, val->reg1, val->reg1 + val->reg2, val->reg3);
	}
}

static void ft_ind_sec(t_env *e, t_carr *car)
{
	t_intstruct val;
	int reg;
	int i;

	//printf("here\n");
	//printf("TESTING NEEDED ALARM ALARM\n");
	//car->reg[1] = 0xffffffff; // find out how to make initialization
	reg = e->fild[car->cur_pos + 2];
	val.reg1 = car->cur_pos + 3;
	val.reg2 = ft_get_value(e, val.reg1, e->funcs[car->command].label);
	val.reg2 = ft_get_value(e, (val.reg2 % IDX_MOD), 4);
	val.reg1 += e->funcs[car->command].label;
	val.reg3 = ft_get_value(e, val.reg1, e->funcs[car->command].label);
	//val.reg2 += val.reg3;
	val.reg3 = car->cur_pos + (val.reg2 + val.reg3) % IDX_MOD;
	ft_flag_sti_show(e, car, reg, &val);
	// printf("val2 %u\n", val.reg3);
	i = -1;
	while (++i < 4)
	{
		//printf("Position %u\n", val.reg3 + i);
		e->fild[val.reg3 + i] = (car->reg[reg] >> (8 * (3 - i)) & 255);
	}
	ft_adv_show(e, car, val.reg1 + 2 - car->cur_pos);
	car->cur_pos = val.reg1 + 2;
	//exit(0);
}


static void	ft_sti(t_env *e, t_carr *car)
{
	t_intstruct val;
	int reg;
	int i;
	int reg1;
	// short value;

	//printf("here\n");
	//car->reg[2] = 0; // find out how to make initialization
	reg = e->fild[car->cur_pos + 2];
	//printf("reg %x\n", reg);
	reg1 = car->cur_pos + 3;
	val.reg2 = (short)ft_get_value(e, reg1, e->funcs[car->command].label);
//	printf("value %d\n", val.reg2);
	reg1 += e->funcs[car->command].label;
	//printf("%\n", e->fild[val.reg1]);
	val.reg3 = (short)ft_get_value(e, reg1, e->funcs[car->command].label);
	val.reg1 = val.reg3;
	//printf("val1 %d\n", val.reg1);	
	val.reg3 = (car->cur_pos + (val.reg3 + val.reg2) % IDX_MOD);
	ft_flag_sti_show(e, car, reg, &val);
	//printf("val2 %d\n", val.reg3);
	i = -1;
	while (++i < 4)
	{
	//	printf("Position simple %u\n", ft_check_pos(val.reg3 + i));
		e->fild[ft_check_pos(val.reg3 + i)] = (car->reg[reg] >> (8 * (3 - i)) & 255);
	}
	ft_adv_show(e, car, reg1 + 2 - car->cur_pos);
	car->cur_pos = reg1 + 2;
	// printf("just sti\n");
	// exit(0);
}

void	ft_sti_hndl(t_env *e, t_carr *car)
{
	if (car->args[1] == IND_CODE)
		ft_ind_sec(e, car);
	else
		ft_sti(e, car);	
}