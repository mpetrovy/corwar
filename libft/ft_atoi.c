/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:27:34 by rsavchak          #+#    #+#             */
/*   Updated: 2017/11/06 19:17:04 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define LONG 9223372036854775807

int	ft_atoi(const char *str)
{
	int						sign;
	static unsigned long	i;
	unsigned long long		res;

	sign = 1;
	i = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
	|| str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = (unsigned long long)(res * 10 + str[i] - '0');
		i++;
		if (res > (long long)LONG && sign == 1)
			return (-1);
		if (res > (long long)LONG && sign == -1)
			return (0);
	}
	return ((int)(res * sign));
}
