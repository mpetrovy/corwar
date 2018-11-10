/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 21:36:21 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 16:24:58 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		*ft_mstr(int n, int len, int check)
{
	char	*arr;
	int		count;

	count = 0;
	if ((arr = (char*)malloc(sizeof(char) * len + check)) == NULL)
		return (NULL);
	if (n == 0)
		arr[count] = '0';
	else
	{
		while (n > 0)
		{
			arr[count] = ((n % 10) + '0');
			n /= 10;
			count++;
		}
	}
	return (arr);
}

static int		ft_nlen(int n)
{
	int count;
	int div;

	div = 1;
	count = 0;
	if (n > 999999999)
		count = 10;
	else if (n == 0)
		count++;
	else
	{
		while (n / div > 0)
		{
			if (n / div > 0)
				count++;
			div *= 10;
		}
	}
	return (count);
}

static char		*ft_fillarr(int len, char *strn, char *arr, int check)
{
	int count;

	count = 0;
	if (check == 2)
	{
		arr[0] = '-';
		count = 1;
	}
	while (--len >= 0)
	{
		arr[count] = strn[len];
		count++;
	}
	arr[count] = '\0';
	return (arr);
}

char			*ft_itoa(int n)
{
	char	*arr;
	int		check;
	char	*strn;
	int		len;

	check = 1;
	if (n < 0 && n != -2147483648)
	{
		check = 2;
		n *= -1;
	}
	else if (n < 0 && n == -2147483648)
		check = 2;
	if ((arr = (char*)malloc(sizeof(char) * ft_nlen(n) + check)) == NULL)
		return (NULL);
	if (check == 2 && n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if ((n < 0 && n != -2147483648) || n >= 0)
	{
		len = ft_nlen(n);
		strn = ft_mstr(n, ft_nlen(n), check);
		arr = ft_fillarr(len, strn, arr, check);
	}
	return (arr);
}
