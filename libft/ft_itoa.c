/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 15:27:51 by rsavchak          #+#    #+#             */
/*   Updated: 2018/01/13 15:27:59 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sign(long long int n)
{
	int sign;

	sign = 0;
	if (n < 0)
	{
		n = n * (-1);
		sign = 1;
	}
	return (sign);
}

char		*ft_itoa(long long int n)
{
	char			*str;
	int				len;
	int				sign;
	long long int	nbr;

	nbr = n;
	len = 1;
	sign = ft_sign(n);
	while (nbr /= 10)
		len++;
	len = len + sign;
	if ((str = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		if (n >= 0)
			str[len] = n % 10 + '0';
		else
			str[len] = '0' - n % 10;
		n = n / 10;
	}
	if (sign)
		*str = '-';
	return (str);
}
