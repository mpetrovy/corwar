#include "vm.h"


static t_values		g_values[17] =
{
	{0, {0}, 0, 0, 0, 0},
	{1, {T_DIR}, 1, 10, 0, 4},
	{2, {T_DIR | T_IND, T_REG}, 2, 5, 1, 4},
	{2, {T_REG, T_IND | T_REG}, 3, 5, 1, 4},
	{3, {T_REG, T_REG, T_REG}, 4, 10, 1, 4},
	{3, {T_REG, T_REG, T_REG}, 5, 10, 1, 4},
	{3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, 1, 4},
	{3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, 1, 4},
	{3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, 1, 4},
	{1, {T_DIR}, 9, 20, 0, 2},
	{3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, 1, 2},
	{3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, 1, 2},
	{1, {T_DIR}, 12, 800, 0, 2},
	{2, {T_DIR | T_IND, T_REG}, 13, 10, 1, 4},
	{3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, 1, 2},
	{1, {T_DIR}, 15, 1000, 0, 2},
	{1, {T_REG}, 16, 2, 1, 4}
};


void	ft_set_data(t_env *e)
{
	int	i;

	i = 0;
	while (i < 17)
	{
		e->funcs[i] = g_values[i];
		i++;
	}
	e->cycle_to_die = CYCLE_TO_DIE;
	e->cur_cycle = 0;
	e->lives = 0;
	e->winner = e->plr_numb;
	e->checks = 0;
	//e->cursors = 0; //maybe delete
	e->carriage_index = 1;
	e->plrs[0].lifes = 0;
	e->plrs[1].lifes = 0;
	e->plrs[2].lifes = 0;
	e->plrs[3].lifes = 0;
}

void	ft_fill_env(t_env *e, int i, int p)
{
	unsigned int j;
	int move;
	int offset;

	ft_bzero(e->fild, MEM_SIZE);
	ft_set_data(e);
	offset = MEM_SIZE / e->plr_numb;
	move = offset;
	while (i < MEM_SIZE)
	{
		j = 0;
		e->plrs[p].plr_pos = i;
		while (j < e->plrs[p].head.prog_size)
		{
			e->fild[i] = e->plrs[p].code[j];
			j++;
			i++;
		}
		i = move;
		move += offset;
		p++;
		if (p == e->plr_numb)
			break ;
	}
}