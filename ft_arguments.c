/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arguments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <rsavchak@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:21:18 by rsavchak          #+#    #+#             */
/*   Updated: 2018/11/28 18:21:19 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	ft_arguments(t_op *ptr, char *line, int com_num)
{
	char	**args;
	int		i;

	args = NULL;
	args = ft_get_arguments(ptr, line);
	ft_arg_validate(args, ptr, 0, com_num);
	ft_bytes(ptr);
	ft_set_code(ptr);
	i = 0;
	if (args)
	{
		while (args[i] != '\0' && i <= 2)
		{
			ft_strdel(&args[i]);
			i++;
		}
	}
}

char	**ft_get_arguments(t_op *ptr, char *line)
{
	int		i;
	char	*arg;
	char	**argument;

	argument = NULL;
	i = 0;
	while (line[i] != '#' && line[i] != ';' && line[i] != '\0')
		i++;
	arg = ft_strsub(line, 0, i);
	if (ft_strchr(arg, ',') == 0)
	{
		argument = ft_memalloc(sizeof(char**));
		argument[0] = ft_strdup(arg);
		argument[1] = NULL;
	}
	else
		argument = ft_strsplit(arg, ',');
	ft_strdel(&arg);
	if (argument[ptr->argc] != NULL)
		ft_error("argument");
	ft_trim(argument, 0, arg);
	return (argument);
}

void	ft_arg_validate(char **args, t_op *ptr, int i, int cnum)
{
	static int tmp[3] = {0, 0, 0};

	while (args[i])
	{
		if (args[i][0] == 'r' && ft_atoi(&args[i][1]) >= 1 && \
			ft_atoi(&args[i][1]) <= 16)
			tmp[i] = T_REG;
		else if (args[i][0] == '%' && (args[i][1] == ':' || \
		args[i][1] == '-' || ft_isdigit(args[i][1])))
			tmp[i] = T_DIR;
		else if (ft_isdigit(args[i][0]) || (args[i][0] == '-' && \
			ft_isdigit(args[i][1])) || (args[i][0] == ':'))
			tmp[i] = T_IND;
		else
			tmp[i] = 42;
		i++;
	}
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == 42)
			ft_error("argument");
		i++;
	}
	ft_parsing_arg(tmp, args, ptr, cnum);
}

void	ft_parsing_arg(int *tmp, char **args, t_op *ptr, int i)
{
	int j;

	j = 0;
	while (args[j])
	{
		if (tmp[j] == T_REG && g_op_tab[i].args[j] % 2 != 0)
			ft_reg(args[j], j, ptr);
		else if (tmp[j] == T_DIR && g_op_tab[i].args[j] != 1 && \
		g_op_tab[i].args[j] != 4 && g_op_tab[i].args[j] != 5)
			ft_dir(args[j], j, ptr, 1);
		else if (tmp[j] == T_IND && g_op_tab[i].args[j] != 1 && \
		g_op_tab[i].args[j] != 2)
			ft_ind(args[j], j, ptr);
		else
			ft_error("argument");
		j++;
	}
}
