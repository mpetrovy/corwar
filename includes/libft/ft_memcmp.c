/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:26:20 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 14:42:56 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str_s1;
	const unsigned char	*str_s2;

	if (s1 == s2 || n == 0)
		return (0);
	str_s1 = (const unsigned char *)s1;
	str_s2 = (const unsigned char *)s2;
	while (n-- != 0)
	{
		if (*str_s1 != *str_s2)
			return (*str_s1 - *str_s2);
		str_s2++;
		str_s1++;
	}
	return (0);
}
