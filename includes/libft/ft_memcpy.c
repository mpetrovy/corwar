/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:28:17 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 14:41:49 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	count;
	void	*arr2;

	if (n == 0 || dest == src)
		return (dest);
	count = 0;
	arr2 = dest;
	while (count < n)
	{
		*(char*)dest = *(char *)src;
		dest++;
		src++;
		count++;
	}
	return (arr2);
}
