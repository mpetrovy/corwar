#include "vm.h"

static void	ft_dir_first(t_env *e, t_carr *car)
{
	unsigned int	value;
	int				pos;
	int				reg;

	pos = car->cur_pos + 2;
	value = ft_get_value(e, pos, e->funcs[car->command].label);
	pos += e->funcs[car->command].label;
	reg = e->fild[pos];
	if (reg > 0 && reg <= REG_NUMBER)
	{
		car->reg[reg] = value;
		(value == 0) ? (car->carry = 1) : (car->carry = 0);
	}
	car->cur_pos = pos + 1;
}

static void	ft_ind_first(t_env *e, t_carr *car)
{
	unsigned int	ind;
	int				pos;
	unsigned int	value;

	pos = car->cur_pos + 2;
 // printf("start %x\n", e->fild[pos]);
 // printf("next %x\n", e->fild[pos + 1]);
 // printf("value %x\n", ft_get_value(e, pos, 2));
	ind = ft_get_value(e, pos, 2);
	// printf("ind %x\n", ind);
	// printf("fild before %x\n", e->fild[pos]);
	// e->fild[pos++] = ((ind >> 8) & 255);
	// printf("fild after %x\n", e->fild[pos - 1]);
	// printf("fild before %x\n", e->fild[pos]);
	//e->fild[pos++] = (ind & 255);
	pos += 2;
//	printf("fild after %x\n", e->fild[pos - 1]);
	value = ft_get_value(e, car->cur_pos + ind, 4);
	//printf("value %x\n", value);
	car->carry = ((value == 0) ? (1) : (0));
	car->reg[e->fild[pos]] = value;
	//printf("reg %x\n", car->reg[e->fild[pos]]);
	car->cur_pos = pos + 1;
//	printf("position %x\n", e->fild[car->cur_pos]);
//	exit(0);
}

void	ft_lld_hndl(t_env *e, t_carr *car)
{
	//printf("LLD HANDLER\n");
	if (car->args[0] == DIR_CODE)
		ft_dir_first(e, car);
	else
		ft_ind_first(e, car);
}
