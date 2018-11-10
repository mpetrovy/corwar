/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 20:18:38 by daalexan          #+#    #+#             */
/*   Updated: 2017/10/28 21:42:16 by daalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*arr;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen((char*)s1) + ft_strlen((char*)s2);
	if ((arr = (char *)malloc(sizeof(*arr) * (size + 1))) == NULL)
		return (NULL);
	if (s1 != NULL && s2 != NULL)
	{
		ft_strcpy(arr, s1);
		ft_strcat(arr, s2);
	}
	return (arr);
}
