/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 17:18:34 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 14:45:35 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*str_s1;
	const unsigned char	*str_s2;

	if (s1 == s2 || n == 0)
		return (0);
	str_s1 = (const unsigned char *)s1;
	str_s2 = (const unsigned char *)s2;
	while ((*str_s1 != '\0' || *str_s2 != '\0') && n--)
	{
		if (*str_s1 != *str_s2)
			return (*str_s1 - *str_s2);
		str_s2++;
		str_s1++;
	}
	return (0);
}
