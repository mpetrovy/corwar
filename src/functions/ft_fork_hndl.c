#include "vm.h"

void	ft_copy(unsigned int *dst, unsigned int *cp)
{
	int i;

	i = 0;
	while (i < REG_NUMBER)
	{
		dst[i] = cp[i];
		i++;
	}
}

static void	ft_add_cursor(t_env *e, t_carr *car, unsigned int pos)
{
	t_carlist *lst;
	t_carlist *tmp;

	tmp = e->head;
	if (!(lst = (t_carlist*)malloc(sizeof(t_carlist))))
		return ;
	lst->carr.cur_pos = car->cur_pos + (pos % IDX_MOD);
	lst->carr.player = car->player;
	lst->carr.car_index = e->cursors + 1;
	lst->carr.carry = car->carry;
	ft_copy(lst->carr.reg, car->reg);
	//lst->carr.reg[0] = car->reg[0];
	//lst->carr.plr_num = nbr;
	lst->carr.alive = car->alive;
	lst->carr.command = 0;
	lst->carr.cycles = 0;
	lst->next = tmp;
	e->head = lst;
}

void	ft_fork_hndl(t_env *e, t_carr *car)
{
	unsigned int	value;


	printf("fork working\n"); 
	value = ft_get_value(e, car->cur_pos + 1, 2);
	ft_add_cursor(e, car, value);
	e->cursors += 1;
	printf("value %x\n", value);
	printf("num car %d\n", e->head->carr.car_index);
	printf("num car next %d\n", e->head->next->carr.car_index);
	printf("value = %x, %x\n", e->head->carr.cur_pos, e->fild[e->head->carr.cur_pos]);
	printf("cursor = %d\n", e->cursors);
	car->cur_pos += 3;
	printf("%x %x %x %x\n", e->fild[car->cur_pos], e->fild[car->cur_pos + 1], e->fild[car->cur_pos + 2], e->fild[car->cur_pos + 3]);
	// exit (0);
}