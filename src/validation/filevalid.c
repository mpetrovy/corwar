/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filevalid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:59:27 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 21:59:28 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	ft_valid_file(char *file)
{
	char	*str;

	str = file;
	if (ft_strcmp(str, "-v") && ft_strcmp(str, "-n") && ft_strcmp(str, "-dump"))
	{
		while (*file)
		{
			if (*file == '.')
			{
				if (!ft_strcmp(file, ".cor"))
					return (1);
				else
					ft_error(str, "file has not valid format");
			}
			file++;
		}
		return (0);
	}
	return (0);
}
