#include "vm.h"

void ft_adv_show(t_env *e, t_carr *car, unsigned int step)
{
	unsigned int i;

	if ((e->flag_num & 16) == 16)
	{
		printf("ADV %u (%s%#.4x -> %#.4x) ", step, ((car->cur_pos == 0) ? ("0x") : ("")),
		car->cur_pos, car->cur_pos + step);//such write
		i = car->cur_pos;
		while (step)
		{
			printf("%.2x ", e->fild[i]);// such output
			i++;
			step--;
		}
		printf("\n");
	}	
}

static unsigned int ft_get_reg(t_env *e, t_carr *car, int *pos)
{
	int reg;

	reg = e->fild[*pos];
	if (reg > 0 && reg <= REG_NUMBER)
	{
		*pos += 1;
		return (car->reg[reg]);
	}
	return (-1);
}

static unsigned int ft_get_dir(t_env *e, t_carr *car, int *pos)
{
	unsigned int value;

	value = ft_get_value(e, *pos, e->funcs[car->command].label);
	*pos += e->funcs[car->command].label;
	return (value);

}

static unsigned int ft_get_ind(t_env *e, t_carr *car, int *pos)
{
	unsigned int value;
	int ind;

	(void)car;
	ind = ft_get_value(e, *pos, 2);
	ind = (*pos + ind % IDX_MOD);
	value = ft_get_value(e, ind, 4);
	*pos += 2;
	return (value);
}

void	ft_set_f(t_get *f)
{
	f[0] = 0;
	f[1] = &ft_get_reg;
	f[2] = &ft_get_dir;
	f[3] = &ft_get_ind;
}