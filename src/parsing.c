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
				e->plrs[p].n_numb = num;
				(*i)++;
				return (1);
			}
			else
				ft_error(av[0], "error is not a number after -n");
		}
		else
			return (0);
	}
	return (1);
}

static void	ft_check_vflag(t_env *e, char **av, int ac)
{
	int i;

	i = 0;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-v"))
		{
			if (av[i + 1] == NULL)
				ft_error("", "can't read source file -v");
			e->flag_num = ft_atoi(av[++i]);
			e->flag_num = (e->flag_num > 31) ? (0) : (e->flag_num);
		}
		else if (!ft_strcmp(av[i], "-dump"))
		{
			if (av[i + 1] == NULL)
				ft_error("", "can't read source file -dump");
			e->dump = ft_atoi(av[++i]);
		}
		i++;
	}
}

void		ft_parse_input(t_env *e, int ac, char **av)
{
	int	i;
	int	p;
	int	res;

	e->plr_numb = 0;
	p = 0;
	i = 1;
	ft_check_vflag(e, av, ac);
	while (i < ac)
	{
		e->plrs[p].n_numb = 0;
		if (!ft_strcmp(av[i], "-n"))
			res = ft_check_flags(e, ac, av, p, &i);
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
