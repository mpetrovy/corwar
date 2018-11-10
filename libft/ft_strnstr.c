/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsavchak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:58:00 by rsavchak          #+#    #+#             */
/*   Updated: 2017/11/05 16:40:40 by rsavchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (s2[i] == '\0')
		return ((char*)s1);
	while (i < len && s1[i] != '\0')
	{
		j = 0;
		while (s2[j] == s1[i + j])
		{
			if ((i + ft_strlen(s2)) > len)
				return (NULL);
			if (s2[j + 1] == '\0')
				return ((char *)(s1 + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
