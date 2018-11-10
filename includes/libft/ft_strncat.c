/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:45:26 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 14:45:27 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	char	*arr;
	size_t	count;

	count = -1;
	arr = dest;
	while (*arr != '\0')
		arr++;
	while (++count < n && *src != '\0')
		*arr++ = *src++;
	*arr = '\0';
	return (dest);
}
