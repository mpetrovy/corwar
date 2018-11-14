#include "vm.h"

static unsigned int ft_get_reg(t_env *e, t_carr *car, int *pos)
{
	int reg;

	printf("get reg\n");
	reg = e->fild[*pos];
	if (reg > 0 && reg <= REG_NUMBER)
	{
		*pos += 1;
		return (car->reg[reg]);
	}
	printf("ERROR\n");
	return (-1);
}

static unsigned int ft_get_dir(t_env *e, t_carr *car, int *pos)
{
	unsigned int value;
	printf("get dir\n");

	value = ft_get_value(e, *pos, e->funcs[car->command].label);
	printf("label %d\n", e->funcs[car->command].label);
	*pos += e->funcs[car->command].label;
	return (value);

}

static unsigned int ft_get_ind(t_env *e, t_carr *car, int *pos)
{
	unsigned int value;
	int ind;

	printf("get ind\n");
	(void)car;
	ind = ft_get_value(e, *pos, 2);
	//printf("ind %d\n", ind);
	ind = (*pos + ind % IDX_MOD);
	//printf("value where %d\n", ind);
	value = ft_get_value(e, ind, 4);
	//printf("value %x\n", value);
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