/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:42:34 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 14:42:36 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*arr1;
	char	*arr2;

	arr1 = (char*)dest;
	arr2 = (char*)src;
	if (arr2 < arr1)
		while (n--)
			arr1[n] = arr2[n];
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
