/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 22:19:41 by daalexan          #+#    #+#             */
/*   Updated: 2018/06/06 22:23:49 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void		ft_putbase(uintmax_t nbr, char *base, size_t len)
{
	if (nbr >= len)
	{
		ft_putbase(nbr / len, base, len);
		ft_putbase(nbr % len, base, len);
	}
	else
		ft_putchar(base[nbr]);
}

void			ft_putnbrbase(uintmax_t nbr, char *base)
{
	ft_putbase(nbr, base, ft_strlen(base));
}
