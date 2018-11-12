#include "vm.h"

void	ft_fill_env(t_env *e, int i, int p)
{
	unsigned int j;
	int move;
	int offset;

	ft_bzero(e->fild, MEM_SIZE);
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