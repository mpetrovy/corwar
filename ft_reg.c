/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_REG.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <rsavchak@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:18:07 by rsavchak          #+#    #+#             */
/*   Updated: 2018/11/28 18:18:09 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	ft_reg(char *args, int i, t_op *ptr)
{
	int k;
	int value;

	k = 1;
	if (args[0] != 'r')
		ft_error("argument");
	while (args[k] != '\0')
	{
		if (ft_isdigit(args[k]) == 0)
			ft_error("argument");
		k++;
	}
	value = ft_atoi(args + 1);
	if (value < 1 || value > 16)
		ft_error("argument");
	ptr->arg[i].type = 1;
	ptr->arg[i].val = value;
	ptr->arg[i].bin = ft_strdup("01");
	ptr->arg[i].labe = NULL;
}

void	ft_dir(char *args, int i, t_op *ptr, int k)
{
	long int value;

	if (args[0] != '%')
		ft_error("argument");
	if (args[1] == ':')
		ft_label_arg(args, i, ptr, 1);
	else
	{
		if (args[1] == '-')
			k = 2;
		while (args[k] != '\0')
		{
			if (ft_isdigit(args[k]) == 0)
				ft_error("argument");
			k++;
		}
		value = ft_atoi(args + 1);
		if (value > 4294967295)
			ft_error("argument");
		ptr->arg[i].type = ptr->labelsize;
		ptr->arg[i].val = value;
		ptr->arg[i].bin = ft_strdup("10");
		ptr->arg[i].labe = NULL;
	}
}

void	ft_label_arg(char *args, int i, t_op *ptr, int k)
{
	char	*str;
	int		j;

	str = NULL;
	j = 0;
	while (args[j] != ':')
		j++;
	str = ft_strdup(args + j + 1);
	j = 0;
	while (str[j] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, str[j]) == 0)
			ft_error("argument label");
		j++;
	}
	ptr->arg[i].labe = ft_strdup(str);
	if (k == 1)
	{
		ptr->arg[i].bin = ft_strdup("10");
		ptr->arg[i].type = ptr->labelsize;
		ptr->arg[i].val = 42;
	}
	ft_strdel(&str);
}

void	ft_ind(char *args, int i, t_op *ptr)
{
	int k;
	int value;

	value = 0;
	k = 0;
	if (args[0] == ':')
		ft_label_arg(args, i, ptr, 0);
	else
	{
		if (args[0] == '-')
			k = 1;
		while (args[k] != '\0')
		{
			if (ft_isdigit(args[k]) == 0)
				ft_error("argument");
			k++;
		}
		value = ft_atoi(args);
		ptr->arg[i].labe = NULL;
	}
	ptr->arg[i].type = 2;
	ptr->arg[i].val = value;
	ptr->arg[i].bin = ft_strdup("11");
}
