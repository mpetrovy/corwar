/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:48:48 by daalexan          #+#    #+#             */
/*   Updated: 2017/11/01 14:48:49 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *arr;

	arr = (char*)s + ft_strlen((char*)s);
	while (*arr != c)
	{
		if (arr == s)
		{
			return (NULL);
		}
		arr--;
	}
	return (arr);
}
