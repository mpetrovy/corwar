/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_err_hndl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 22:05:33 by daalexan          #+#    #+#             */
/*   Updated: 2018/11/28 22:05:34 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_error(char *file, char *err_mess)
{
	ft_putstr("Error: ");
	ft_putstr(file);
	ft_putchar(' ');
	ft_putstr(err_mess);
	ft_putchar('\n');
	exit(-1);
}
