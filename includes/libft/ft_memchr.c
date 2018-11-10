/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:41:28 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 14:41:32 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*arr1;
	size_t			index;

	index = -1;
	arr1 = (unsigned char*)s;
	while (++index < n)
	{
		if (*arr1 == (unsigned char)c)
			return (arr1);
		arr1++;
	}
	return (NULL);
}
