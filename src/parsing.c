#include "vm.h"

static void	ft_check_flag_value(char *str)
{
	while(*str)
	{
		if (*str >= '0' && *str <= '9')
			str++;
		else
			ft_error("-n", "is not a number");
	}
}

static int	ft_check_flags(t_env *e, int ac, char **av, int p, int *i)
{
	unsigned int num;

	num = 0;
	while (*i < ac)
	{
		if (!ft_strcmp(av[*i], "-n"))
		{
			(*i)++;
			ft_check_flag_value(av[*i]);
			num = ft_atoi(av[*i]);
			if (num < 4294967295 || num == 4294967295)
			{
				//printf("value = %u\n", num);
				e->plrs[p].n_numb = num;
				(*i)++;
			//	printf("value1 = %u\n", e->plrs[p].n_numb);
				return (1);
				//return ((ft_valid_file(av[*i])) ? (1) : (0));
			}
			else
				ft_error(av[0], "error is not a number after -n");
		}
		else
			return (0);
	}
	return (1);
}

int			ft_check_vflag(char **av, int *i)
{
	if (!ft_strcmp(av[*i], "-v"))
	{
		//printf("flag = %s\n", av[*i]);
		(*i)++;
		//printf("value = %s\n", av[*i]);
		return (ft_atoi(av[(*i)++]));
	}
	return (0);
}

void		ft_parse_input(t_env *e, int ac, char **av)
{
	int i;
	int p;
	int res;

	e->plr_numb = 0;
	p = 0;
	i = 1;
	while (i < ac)
	{
		e->plrs[p].n_numb = 0;
		if (!ft_strcmp(av[i], "-n") || !ft_strcmp(av[i], "-v"))
		{
			res = ft_check_flags(e, ac, av, p, &i);
			e->flag_num = ft_check_vflag(av, &i);
		}
		if (i != ac && ft_valid_file(av[i]))
		{
			if (!res)
				e->plrs[p].n_numb = 4294967295 - p;
			e->plrs[p++].file_name = av[i];
			e->plr_numb++;
		}
		if (e->plr_numb > MAX_PLAYERS)
			ft_error("./corewar", "to much players");
		i++;
	}
}
