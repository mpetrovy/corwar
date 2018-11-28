/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <rsavchak@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:28:54 by rsavchak          #+#    #+#             */
/*   Updated: 2018/11/28 18:28:55 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	ft_set_code(t_op *ptr)
{
	int		i;
	char	*code;
	char	*z;

	code = NULL;
	i = 1;
	if (ptr->codage == 1)
	{
		code = ft_strdup(ptr->arg[0].bin);
		while (ptr->arg[i].bin && i <= 2)
		{
			z = code;
			code = ft_strjoin(code, ptr->arg[i].bin);
			ft_strdel(&z);
			i++;
		}
		if (ft_strlen(code) == 6)
			code = ft_strjoin(code, "00");
		else if (ft_strlen(code) == 4)
			code = ft_strjoin(code, "0000");
		ptr->cod = ft_atoi_base(code, 2);
		ft_strdel(&code);
	}
	else
		ptr->cod = 0;
}

void	ft_bytes(t_op *ptr)
{
	int i;
	int byte_count;

	i = 0;
	byte_count = 0;
	while (ptr->arg[i].type && i <= 2)
	{
		byte_count = byte_count + ptr->arg[i].type;
		i++;
	}
	ptr->bytes = byte_count + ptr->codage + 1;
}
