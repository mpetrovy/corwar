/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 20:35:49 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 14:42:09 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*arr;
	size_t			count;

	count = -1;
	arr = (unsigned char*)s;
	if (n == 0)
		return (s);
	while (++count < n)
		arr[count] = (unsigned char)c;
	return (s);
}
