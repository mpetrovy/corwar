/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 15:43:55 by rsavchak          #+#    #+#             */
/*   Updated: 2017/11/01 18:17:58 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;
	size_t res;

	j = 0;
	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	res = ft_strlen(src);
	while (dst[i] != '\0' && i < dstsize)
		i++;
	while (src[j] != '\0' && i < dstsize - 1)
		dst[i++] = src[j++];
	if (j > 0)
	{
		dst[i] = '\0';
		return (res + i - j);
	}
	return (res + i);
}
