/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 17:41:17 by rsavchak          #+#    #+#             */
/*   Updated: 2018/09/13 17:41:21 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_len_and_sign(unsigned long long int value, int *len, int base)
{
	unsigned long long nbr;

	nbr = value;
	while (nbr)
	{
		nbr = nbr / base;
		*len = *len + 1;
	}
	nbr = value;
	if (nbr == -0)
		return (0);
	return (nbr);
}

char	*ft_itoa_base(unsigned long long int value, int base)
{
	int						len;
	unsigned long long		nbr;
	char					*str;
	const char				*base_string = "0123456789abcdef";

	if (value == 0)
	{
		str = ft_strdup("0");
		return (str);
	}
	len = 0;
	nbr = ft_len_and_sign(value, &len, base);
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len] = '\0';
	while (nbr)
	{
		str[--len] = base_string[nbr % base];
		nbr /= base;
	}
	return (str);
}
